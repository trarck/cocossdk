import os
import os.path
import zipfile
import re
import subprocess
import platform
from config import ConfigParse
import inspect
import sys
import codecs
import threading
import time
#import error_operate

PRINTABLE = True
LANGUAGE = 'Chinese'
CURRENT_DIR = os.getcwd()

def delete_file_folder(src):
    if os.path.exists(src):
        if os.path.isfile(src):
            try:
                src = src.replace('\\', '/')
                os.remove(src)
            except:
                pass

        elif os.path.isdir(src):
            for item in os.listdir(src):
                itemsrc = os.path.join(src, item)
                delete_file_folder(itemsrc)

            try:
                os.rmdir(src)
            except:
                pass


def copy_files(sourceDir, targetDir):
    if not os.path.exists(sourceDir) and not os.path.exists(targetDir):
        printf('copy Files from %s to %s Fail:file not found' % (sourceDir, targetDir))
        return
    if os.path.isfile(sourceDir):
        copy_file(sourceDir, targetDir)
        return
    for file in os.listdir(sourceDir):
        sourceFile = os.path.join(sourceDir, file)
        targetFile = os.path.join(targetDir, file)
        if os.path.isfile(sourceFile):
            if not os.path.exists(targetDir):
                os.makedirs(targetDir)
            if not os.path.exists(targetFile) or os.path.exists(targetFile) and os.path.getsize(targetFile) != os.path.getsize(sourceFile):
                targetFileHandle = open(targetFile, 'wb')
                sourceFileHandle = open(sourceFile, 'rb')
                targetFileHandle.write(sourceFileHandle.read())
                targetFileHandle.close()
                sourceFileHandle.close()
        if os.path.isdir(sourceFile):
            copy_files(sourceFile, targetFile)


def copy_file(sourceFile, targetFile):
    sourceFile = get_full_path(sourceFile)
    targetFile = get_full_path(targetFile)
    if not os.path.exists(sourceFile):
        return
    if not os.path.exists(targetFile) or os.path.exists(targetFile) and os.path.getsize(targetFile) != os.path.getsize(sourceFile):
        targetDir = os.path.dirname(targetFile)
        if not os.path.exists(targetDir):
            os.makedirs(targetDir)
        targetFileHandle = open(targetFile, 'wb')
        sourceFileHandle = open(sourceFile, 'rb')
        targetFileHandle.write(sourceFileHandle.read())
        targetFileHandle.close()
        sourceFileHandle.close()


def copy_apk_to_zip(filename):
    dotIndex = filename.find('.')
    newfilename = filename
    if dotIndex >= 0 and os.path.exists(filename):
        name = filename[:dotIndex]
        ext = filename[dotIndex:]
        newext = '.zip'
        newfilename = name + newext
        if not os.path.exists(newfilename) or os.path.exists(newfilename) and os.path.getsize(newfilename) != os.path.getsize(filename):
            targetFileHandle = open(newfilename, 'wb')
            sourceFileHandle = open(filename, 'rb')
            targetFileHandle.write(sourceFileHandle.read())
            targetFileHandle.close()
            sourceFileHandle.close()
            printf('copy success')


def decompression(filename, unziptodir):
    delete_file_folder(unziptodir)
    if not os.path.exists(unziptodir):
        os.mkdir(unziptodir, 511)
    f = zipfile.ZipFile(filename)
    f.extractall(unziptodir)
    printf('decompression success!')
    f.close()
    delete_file_folder(filename)


def get_current_dir():
    global CURRENT_DIR
    retPath = CURRENT_DIR
    if platform.system() == 'Windows':
        retPath = retPath.decode('gbk')
    return retPath


def get_full_path(filename):
    if os.path.isabs(filename):
        return filename
    dirname = get_current_dir()
    filename = os.path.join(dirname, filename)
    filename = filename.replace('\\', '/')
    filename = re.sub('/+', '/', filename)
    return filename


def get_tool_path(filename):
    toolPath = ''
    if platform.system() == 'Darwin':
        toolPath = get_full_path('../tool/mac/' + filename)
    else:
        toolPath = get_full_path('../tool/win/' + filename)
    return toolPath


def modify_file_content_by_binary(source, oldContent, newContent):
    f = open(source, 'rb')
    data = f.read()
    f.close()
    bRet = False
    idx = data.find(oldContent)
    while idx != -1:
        data = data[:idx] + newContent + data[idx + len(oldContent):]
        idx = data.find(oldContent, idx + len(oldContent))
        bRet = True

    if bRet:
        fhandle = open(source, 'wb')
        fhandle.write(data)
        fhandle.close()


def modify_file_content(source, fileType, oldContent, newContent):
    if os.path.isdir(source):
        for file in os.listdir(source):
            sourceFile = os.path.join(source, file)
            modify_file_content(sourceFile, fileType, oldContent, newContent)

    elif os.path.isfile(source) and os.path.splitext(source)[1] == fileType:
        f = open(source, 'r+')
        data = str(f.read())
        f.close()
        bRet = False
        idx = data.find(oldContent)
        while idx != -1:
            data = data[:idx] + newContent + data[idx + len(oldContent):]
            idx = data.find(oldContent, idx + len(oldContent))
            bRet = True
        if bRet:
            fhandle = open(source, 'w')
            fhandle.write(data)
            fhandle.close()
            printf('modify file:%s' % source)
        #else:
            #error_operate.error(108)

def exec_format_cmd(cmd):
    cmd = cmd.replace('\\', '/')
    cmd = re.sub('/+', '/', cmd)
    ret = 0
    if platform.system() == 'Windows':
        st = subprocess.STARTUPINFO
        st.dwFlags = subprocess.STARTF_USESHOWWINDOW
        st.wShowWindow = subprocess.SW_HIDE
        cmd = str(cmd).encode('gbk')
    s = subprocess.Popen(cmd, shell=True)
    ret = s.wait()
    if ret:
        s = subprocess.Popen(cmd, stdout=subprocess.PIPE, stderr=subprocess.PIPE, shell=True)
        stdoutput, erroutput = s.communicate()
        report_cmd_error(cmd, stdoutput, erroutput)
        cmd = 'ERROR:' + cmd + ' ===>>> exec Fail <<<=== '
    else:
        cmd += ' ===>>> exec success <<<=== '
    printf(cmd)
    return ret


def get_apk_version(apkFile):
    """get the version about apk"""
    cmd = '"' + get_tool_path('aapt') + '" d badging "' + apkFile + '"'
    cmd = cmd.replace('\\', '/')
    cmd = re.sub('/+', '/', cmd)
    ret = 0
    if platform.system() == 'Windows':
        st = subprocess.STARTUPINFO
        st.dwFlags = subprocess.STARTF_USESHOWWINDOW
        st.wShowWindow = subprocess.SW_HIDE
        cmd = str(cmd).encode('gbk')
    s = subprocess.Popen(cmd, stdout=subprocess.PIPE, shell=True)
    info = s.communicate()[0]
    nPos = info.find('versionName')
    nEnd = info.find("'", nPos + 13)
    versionName = info[nPos + 13:nEnd]
    if versionName == '':
        versionName = 'Unknown Version'
    return versionName


def get_target_sdk_version(apkFile):
    cmd = get_tool_path('aapt') + " d badging '" + apkFile + "'"
    cmd = cmd.replace('\\', '/')
    cmd = re.sub('/+', '/', cmd)
    cmd = str(cmd).encode('utf-8')
    ret = 0
    if platform.system() == 'Windows':
        st = subprocess.STARTUPINFO
        st.dwFlags = subprocess.STARTF_USESHOWWINDOW
        st.wShowWindow = subprocess.SW_HIDE
    s = subprocess.Popen(cmd, stdout=subprocess.PIPE, shell=True)
    info = s.communicate()[0]
    nPos = info.find('targetSdkVersion')
    nEnd = info.find("'", nPos + 18)
    sdkVersionName = info[nPos + 18:nEnd]
    return int(sdkVersionName)


def backup_apk(source, game, versionName):
    gameName = game['gameName']
    outputDir = ConfigParse.share_instance().get_output_dir()
    if outputDir == '':
        outputDir = '../output/'
    outputDir += '/' + game['gameName'] + '/' + versionName + '/common'
    outputDir = get_full_path(outputDir)
    backupName = '%s/common.apk' % outputDir
    if os.path.exists(backupName):
        os.remove(backupName)
    copy_file(source, backupName)


def get_java_bin_dir():
    javaBinDir = ''
    return javaBinDir


def get_java():
    if platform.system() == 'Darwin':
        javaPath = os.path.join(CURRENT_DIR, '../tool/mac/jre/bin/')
        if os.path.exists(javaPath):
            return javaPath + 'java'
        else:
            return get_java_bin_dir() + 'java'
    else:
        return get_java_bin_dir() + 'java'


def printf(str):
    """
    print info in debug mode
    or
    write info into pythonLog.txt in release mode
    """
    global PRINTABLE
    if PRINTABLE:
        print str


def report_cmd_error(cmd, stdoutput, erroutput):
    """
    """
    errorLog = stdoutput + '\r\n' + erroutput
    report_error(errorLog, int(threading.currentThread().getName()))


def report_error(errorOuput, idChannel):
    """
    """
    packageName = ''
    channel = ConfigParse.shareInstance().findChannel(idChannel)
    if channel != None and channel.get('packNameSuffix') != None:
        packageName = str(channel['packNameSuffix'])
        channelName = str(channel['name'])
        if platform.system() == 'Windows':
            channelName = str(channel['name']).encode('gbk')
        else:
            channelName = channel['name'].decode('utf8').encode('gbk')
    error = '==================>>>> ERROR <<<<==================\r\n'
    error += '[AnySDK_Channel]: ' + threading.currentThread().getName() + '\r\n'
    error += '[AnySDK_ChannelName]: ' + channelName + '\r\n'
    error += '[AnySDK_Package]: ' + packageName + '\r\n'
    error += '[AnySDK_Time]: ' + time.strftime('%Y-%m-%d %H:%M:%S', time.localtime(time.time())) + '\r\n'
    error += '[AnySDK_Error]:\r\n'
    error += errorOuput + '\r\n'
    error += '===================================================\r\n'
    log(error)


def log(str):
    outputDir = ConfigParse.shareInstance().getOutputDir()
    logDir = outputDir + '/log/'
    if not os.path.exists(logDir):
        os.makedirs(logDir)
    logFile = codecs.open(logDir + 'error.txt', 'a+', 'utf-8')
    content = str + '\r\n'
    if platform.system() == 'Windows':
        logFile.write(unicode(content, 'gbk'))
    else:
        logFile.write(unicode(content, 'gbk'))
    logFile.close()


def set_print_enable(bEnable):
    global PRINTABLE
    global CURRENT_DIR
    PRINTABLE = bEnable
    CURRENT_DIR = sys.path[0]
