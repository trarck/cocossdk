#Embedded file name: C:\Users\Administrator\Desktop\Env\Script\config.py
import threading
from xml.etree import ElementTree as ET
import re
import os
import file_operate
import sqlite3
import platform
#from modifyProject import XcodeProject
from xml.dom import minidom
import codecs
import re
#from modifyPlist import *

class ConfigParse(object):
    """The class can parse project config file of xml """

    def __init__(self):
        """disable the __init__ method"""
        pass

    __configParse = None
    __lock = threading.Lock()
    _source = ''
    __appName = ''
    __iOSName = ''
    _projFolder = ''
    _projXcode = ''
    _projSDKVersion = ''
    _projSDKPath = ''
    _projIpaPackage = ''
    _outputDir = ''
    _keystore = {}
    _oldPackagename = ''
    _packagename = ''
    __gameLs = []
    __gamekey = 0
    __gameVersionName = ''
    __SDKLs = {}
    __channelCustomLs = {}
    __channelLs = {}
    __userSDKConfigLs = {}
    __packageLs = []
    __SDKVersionLs = []
    __isCocosPlayMode = False

    @staticmethod
    def shareInstance():
        ConfigParse.__lock.acquire()
        if not ConfigParse.__configParse:
            ConfigParse.__configParse = object.__new__(ConfigParse)
            object.__init__(ConfigParse.__configParse)
            ConfigParse.__configParse.projectConfigRead()
        ConfigParse.__lock.release()
        return ConfigParse.__configParse

    def projectConfigRead(self):
        """Read config.xml file and save to a dictionary"""
        self.initDatabase()

    def readUserConfig(self, platform):
        """read config about user choice"""
        self.addLibPath()
        self.readUserDatabase()
        if platform == 0:
            self.__gameVersionName = file_operate.getApkVersion(self._source)
        elif platform == 1:
            self.__gameVersionName = self.getIosProjectVersion()

    def getSource(self):
        return self._source

    def getAppName(self):
        return self.__appName

    def getIosName(self):
        return self.__iOSName

    def getProjFolder(self):
        return self._projFolder

    def getProjXcode(self):
        return self._projXcode

    def getProjSDKVersion(self):
        return self._projSDKVersion

    def getProjSDKPath(self):
        return self._projSDKPath

    def getProjIpaPackage(self):
        return self._projIpaPackage

    def getOutputDir(self):
        return self._outputDir

    def getKeyStore(self):
        return self._keystore

    def getGamekey(self):
        return self.__gamekey

    def getVersionName(self):
        return self.__gameVersionName

    def initDatabase(self):
        """get the data from database."""
        dbPath = os.path.join(file_operate.getCurDir(), '../config/config.db')
        cx = sqlite3.connect(dbPath)
        cx.row_factory = sqlite3.Row
        self.readSDKLs(cx)
        cx.close()

    def readUserDatabase(self):
        """get the config about user's sdk from database"""
        dbPath = os.path.join(file_operate.getCurDir(), '../config/config.db')
        cx = sqlite3.connect(dbPath)
        cx.row_factory = sqlite3.Row
        self.readSDKVersionLs(cx)
        self.readChannelCustomLs(cx)
        self.readChannel(cx)
        self.readChannelSdk(cx)
        self.readUserSDKConfig(cx)
        self.readUserSDKParam(cx)
        self.readGameLs(cx)
        self.readUserSource(cx)
        self.readProjFolder(cx)
        self.readProjSDKPath(cx)
        self.readOutputDir(cx)
        self.readPackage(cx)
        cx.close()
        game = self.getCurrentGame()
        if game is None:
            return
        self._keystore['file'] = game['keystoreFile']
        self._keystore['storepassword'] = game['keystorePwd']
        self._keystore['keyalias'] = game['keystoreAlias']
        self._keystore['aliaspassword'] = game['keystoreAliasPwd']

    def readSDKLs(self, cx):
        """get the data about tpl_sdk from database"""
        self.__SDKLs.clear()
        c = cx.cursor()
        c.execute('select * from tpl_sdk')
        rows = c.fetchall()
        for r in rows:
            dictTemp = {}
            dictTemp['idSDK'] = r['idSDK']
            dictTemp['SDKName'] = r['SDKName']
            dictTemp['pluginxType'] = r['pluginxType']
            dictTemp['SDKShowName'] = r['SDKShowName']
            dictTemp['bHasChildSDK'] = r['bHasChildSDK']
            dictTemp['orderCallback'] = r['orderCallback']
            dictTemp['operateLs'] = []
            dictTemp['pluginLs'] = []
            dictTemp['SDKLs'] = []
            self.__SDKLs[dictTemp['idSDK']] = dictTemp

        c.close()

    def readChannelCustomLs(self, cx):
        """get the data about tpl_channel_customer from database"""
        self.__channelCustomLs.clear()
        c = cx.cursor()
        c.execute('select * from tpl_channel_customer')
        rows = c.fetchall()
        for r in rows:
            dictTemp = {}
            dictTemp['channelNum'] = r['channelNum']
            dictTemp['channelName'] = r['channelName']
            dictTemp['channelPlatform'] = r['channelPlatform']
            dictTemp['channelSequence'] = r['channelSequence']
            dictTemp['customChannelNumber'] = r['customChannelNumber']
            dictTemp['publicChannelNum'] = r['publicChannelNum']
            self.__channelCustomLs[dictTemp['channelNum']] = dictTemp

        c.close()

    def readSDKVersionLs(self, cx):
        """get the data about tpl_sdk from database"""
        self.__SDKVersionLs = []
        c = cx.cursor()
        c.execute('select * from tpl_version')
        rows = c.fetchall()
        for r in rows:
            dictTemp = {}
            dictTemp['name'] = r['name']
            dictTemp['version'] = r['version']
            dictTemp['type'] = r['type']
            dictTemp['showVersion'] = r['showVersion']
            self.__SDKVersionLs.append(dictTemp)

        c.close()

    def readChannel(self, cx):
        """get the data about tpl_channel from database"""
        self.__channelLs.clear()
        c = cx.cursor()
        c.execute('select * from tpl_channel')
        rows = c.fetchall()
        for r in rows:
            dictTemp = {}
            dictTemp['idChannel'] = r['idChannel']
            dictTemp['channelNum'] = r['channelNum']
            dictTemp['name'] = r['name']
            dictTemp['idGame'] = r['idGame']
            dictTemp['packNameSuffix'] = r['packNameSuffix']
            dictTemp['keystoreFile'] = r['keystoreFile']
            dictTemp['keystorePwd'] = r['keystorePwd']
            dictTemp['keystoreAlias'] = r['keystoreAlias']
            dictTemp['keystoreAliasPwd'] = r['keystoreAliasPwd']
            dictTemp['uapiKey'] = r['uapiKey']
            dictTemp['uapiSecret'] = r['uapiSecret']
            dictTemp['oauthLoginServer'] = r['oauthLoginServer']
            dictTemp['bHasSplash'] = r['bHasSplash']
            dictTemp['extChannel'] = r['extChannel']
            dictTemp['jsonMeta'] = r['jsonMeta']
            dictTemp['customChannelNumber'] = r['customChannelNumber']
            dictTemp['sdkLs'] = []
            self.__channelLs[dictTemp['idChannel']] = dictTemp

        c.close()

    def readChannelSdk(self, cx):
        """get the data about sdk in channel from database"""
        c = cx.cursor()
        c.execute('select * from tpl_channel_sdk')
        rows = c.fetchall()
        for r in rows:
            dictTemp = {}
            dictTemp['id'] = r['id']
            dictTemp['idChannel'] = r['idChannel']
            dictTemp['idSDK'] = r['idSDK']
            dictTemp['type'] = r['type']
            dictTemp['childSDK'] = r['childSDK']
            dictTemp['notify_url'] = r['notify_url']
            idChannel = dictTemp['idChannel']
            channel = self.__channelLs.get(idChannel)
            if channel != None:
                channel['sdkLs'].append(dictTemp)

        c.close()

    def readUserSDKConfig(self, cx):
        """get the data about tpl_user_sdk_config from database"""
        self.__userSDKConfigLs.clear()
        c = cx.cursor()
        c.execute('select * from tpl_user_sdk_config')
        rows = c.fetchall()
        for r in rows:
            dictTemp = {}
            dictTemp['idUserSDK'] = r['idUserSDK']
            dictTemp['name'] = r['name']
            dictTemp['idChannel'] = r['idChannel']
            dictTemp['idSDK'] = r['idSDK']
            dictTemp['showName'] = r['showName']
            dictTemp['type'] = r['type']
            dictTemp['childSDK'] = r['childSDK']
            dictTemp['notify_url'] = r['notify_url']
            dictTemp['param'] = []
            self.__userSDKConfigLs[dictTemp['idUserSDK']] = dictTemp

        c.close()

    def readUserSDKParam(self, cx):
        """get the data about tpl_user_sdk_param from database"""
        c = cx.cursor()
        c.execute('select * from tpl_user_sdk_param')
        rows = c.fetchall()
        for r in rows:
            dictTemp = {}
            dictTemp['id'] = r['id']
            dictTemp['name'] = r['name']
            dictTemp['value'] = r['value'][1:]
            dictTemp['idUserSDK'] = r['idUserSDK']
            dictTemp['required'] = r['required']
            dictTemp['bWriteIntoManifest'] = r['bWriteIntoManifest']
            dictTemp['bUserOffer'] = r['bUserOffer']
            dictTemp['bWriteIntoClient'] = r['bWriteIntoClient']
            sdkItem = self.__userSDKConfigLs.get(dictTemp['idUserSDK'])
            if sdkItem != None:
                sdkItem['param'].append(dictTemp)

        c.close()

    def readUserSource(self, cx):
        """read apk src from user.xml"""
        data = self.readConfig(1)
        if data is not None:
            self._source = data['data1']
            if data.get('data4') is not None:
                self.__appName = data['data4']

    def readOutputDir(self, cx):
        """read output dir from user.xml"""
        data = self.readConfig(2)
        if data is None:
            if platform.system() == 'Darwin':
                self._outputDir = '../../../output/'
            else:
                self._outputDir = '../output/'
        else:
            self._outputDir = data['data1']

    def readProjFolder(self, cx):
        data = self.readConfig(6)
        if data is not None:
            self._projFolder = data['data1']
            self._projXcode = data['data2']
            self._projSDKVersion = data['data3']
            self._projIpaPackage = data['data4']
            if data.get('data5') is not None:
                self.__iOSName = data['data5']

    def readProjSDKPath(self, cx):
        data = self.readConfig(7)
        if data is not None:
            self._projSDKPath = data['data1']

    def readConfig(self, type):
        """
            read config from config/user.xml
            @param type:
                1:apk src
                2:out dir
                3:user name
        """
        configPath = '../config/user.xml'
        configPath = file_operate.getFullPath(configPath)
        if not os.path.exists(configPath):
            return
        targetTree = ET.parse(configPath)
        targetRoot = targetTree.getroot()
        if targetRoot is None:
            return
        dataLsNode = targetRoot.findall('data')
        if dataLsNode is None:
            return
        for dataNode in dataLsNode:
            dictTemp = {}
            dictTemp['type'] = dataNode.get('type')
            dictTemp['data1'] = dataNode.get('data1')
            dictTemp['data2'] = dataNode.get('data2')
            dictTemp['data3'] = dataNode.get('data3')
            dictTemp['data4'] = dataNode.get('data4')
            dictTemp['data5'] = dataNode.get('data5')
            dictTemp['desc'] = dataNode.get('desc')
            if dictTemp['type'] is not None and int(dictTemp['type']) == type:
                return dictTemp

    def readGameLs(self, cx):
        """get the data about game list from database"""
        self.__gameLs = []
        c = cx.cursor()
        c.execute('select * from game')
        rows = c.fetchall()
        for r in rows:
            dictTemp = {}
            dictTemp['gameId'] = r['gameId']
            dictTemp['gameName'] = r['gameName']
            dictTemp['gameType'] = r['gameType']
            dictTemp['gameIcon'] = r['gameIcon']
            dictTemp['gameTelephone'] = r['gameTelephone']
            dictTemp['gameQQ'] = r['gameQQ']
            dictTemp['gameWx'] = r['gameWx']
            dictTemp['gameWeibo'] = r['gameWeibo']
            dictTemp['gameIconPos'] = r['gameIconPos']
            dictTemp['gameIconOffsetX'] = r['gameIconOffsetX']
            dictTemp['gameIconOffsetY'] = r['gameIconOffsetY']
            dictTemp['keystoreFile'] = r['keystoreFile']
            dictTemp['keystorePwd'] = r['keystorePwd']
            dictTemp['keystoreAlias'] = r['keystoreAlias']
            dictTemp['keystoreAliasPwd'] = r['keystoreAliasPwd']
            dictTemp['privateKey'] = r['privateKey']
            dictTemp['order_url'] = r['order_url']
            dictTemp['isModifyAppName'] = r['isModifyAppName']
            dictTemp['isModifyiOSName'] = r['isModifyiOSName']
            self.__gameLs.append(dictTemp)

        c.close()

    def readPackage(self, cx):
        """get the data about tpl_package from database"""
        self.__packageLs = []
        c = cx.cursor()
        c.execute('select * from tpl_package')
        rows = c.fetchall()
        for r in rows:
            dictTemp = {}
            dictTemp['id'] = r['id']
            dictTemp['idChannel'] = r['idChannel']
            self.__packageLs.append(dictTemp)

        if self.__packageLs.__len__ > 0:
            idChannel = self.__packageLs[0]['idChannel']
            self.__gamekey = self.__channelLs[idChannel]['idGame']
        c.close()

    def findGame(self, gameId):
        for item in self.__gameLs:
            if str(item['gameId']) == str(gameId):
                return item

    def getCurrentGame(self):
        return self.findGame(self.__gamekey)

    def getChannelLs(self):
        return self.__channelLs

    def getSDKLs(self):
        return self.__SDKLs

    def getPackageLs(self):
        return self.__packageLs

    def getUserSDKConfig(self):
        return self.__userSDKConfigLs

    def findChannel(self, idChannel):
        return self.__channelLs[idChannel]

    def findCustomChannel(self, channelNum):
        return self.__channelCustomLs.get(channelNum)

    def findSDK(self, idSDK):
        """check SDK whether has OperateLs"""
        SDK = self.__SDKLs.get(idSDK)
        if SDK is None:
            return SDK
        while True:
            if SDK['operateLs'] is not None and len(SDK['operateLs']) > 0:
                break
            configPath = '../config/sdk/' + SDK['SDKName'] + '/config.xml'
            configPath = file_operate.getFullPath(configPath)
            if not os.path.exists(configPath):
                break
            targetTree = ET.parse(configPath)
            targetRoot = targetTree.getroot()
            if targetRoot is None:
                break
            operateLsNode = targetRoot.find('operateLs')
            if operateLsNode is None:
                break
            for operateNode in operateLsNode:
                dictTemp = {}
                dictTemp['name'] = operateNode.get('name')
                if operateNode.get('step') is not None:
                    dictTemp['step'] = int(operateNode.get('step'))
                dictTemp['from'] = operateNode.get('from')
                dictTemp['to'] = operateNode.get('to')
                dictTemp['desc'] = operateNode.get('desc')
                dictTemp['idSDK'] = int(SDK.get('idSDK'))
                SDK['operateLs'].append(dictTemp)

            if SDK['pluginLs'] is not None and len(SDK['pluginLs']) > 0:
                break
            pluginLsNode = targetRoot.find('pluginLs')
            if pluginLsNode is None:
                break
            for pluginNode in pluginLsNode:
                dictTemp = {}
                dictTemp['name'] = pluginNode.get('name')
                if pluginNode.get('typePlugin') is not None:
                    dictTemp['typePlugin'] = int(pluginNode.get('typePlugin'))
                dictTemp['desc'] = pluginNode.get('desc')
                dictTemp['idSDK'] = int(SDK.get('idSDK'))
                SDK['pluginLs'].append(dictTemp)

            if not SDK['bHasChildSDK']:
                break
            if SDK['SDKLs'] is not None and len(SDK['SDKLs']) > 0:
                break
            SDKLsNode = targetRoot.find('SDKLs')
            if SDKLsNode is None:
                break
            for SDKNode in SDKLsNode:
                dictTemp = {}
                dictTemp['SDKName'] = SDKNode.get('SDKName')
                dictTemp['SDKType'] = SDKNode.get('SDKType')
                dictTemp['SDKShowName'] = SDKNode.get('SDKShowName')
                ParamLsNode = SDKNode.find('param')
                if ParamLsNode is None:
                    continue
                for param in ParamLsNode:
                    dictParam = {}
                    dictParam['name'] = param.get('name')
                    dictParam['required'] = param.get('required')
                    dictParam['desc'] = param.get('desc')
                    dictParam['showName'] = param.get('showName')
                    dictParam['bWriteIntoManifest'] = param.get('bWriteIntoManifest')
                    dictParam['bWriteIntoClient'] = param.get('bWriteIntoClient')
                    dictTemp['param'] = dictParam

                SDK['SDKLs'].append(dictTemp)

            break

        return self.__SDKLs[idSDK]

    def findUserSDKConfig(self, idUserSDK):
        return self.__userSDKConfigLs[idUserSDK]

    def findUserSDKConfigBySDK(self, idSDK, idChannel):
        for usrConfig in self.__userSDKConfigLs.values():
            if usrConfig['idSDK'] == idSDK and usrConfig['idChannel'] == idChannel:
                return usrConfig

    def findSDKVersion(self, SDKName):
        for version in self.__SDKVersionLs:
            if version['type'] == 1 and version['name'] == SDKName:
                return version

    def addLibPath(self):
        if platform.system() == 'Darwin':
            libPath = file_operate.getToolPath('')
            os.environ['PATH'] = libPath + ':' + os.environ['PATH']
            if os.path.exists('/System/Library/Frameworks/JavaVM.framework/Versions/Current/Commands/'):
                libPath = ':' + '/System/Library/Frameworks/JavaVM.framework/Versions/Current/Commands/'
                os.environ['PATH'] = libPath + ':' + os.environ['PATH']
        elif platform.system() == 'Windows':
            libPath = file_operate.getToolPath('')
            libPath = libPath.encode('gbk')
            os.environ['PATH'] = libPath + ';' + os.environ['PATH']
            jrePath = file_operate.getToolPath('jre/bin')
            jrePath = jrePath.encode('gbk')
            os.environ['PATH'] = jrePath + ';' + os.environ['PATH']

    def getIosProjectVersion(self):
		"""
        pbxFile = self._projFolder + '/' + self._projXcode + '/project.pbxproj'
        project = XcodeProject.Load(pbxFile)
        project_infoplist = self._projFolder + '/' + self._projXcode + '/../' + project.get_infoplistfile()
        if not os.path.exists(project_infoplist):
            return '1.0'
        try:
            plist = readPlist(project_infoplist)
            versionNumber = ''
            for key in plist:
                if key == 'CFBundleShortVersionString':
                    versionNumber = plist['CFBundleShortVersionString']
                elif key == 'CFBundleVersion':
                    if versionNumber == '':
                        versionNumber = plist['CFBundleVersion']

            if versionNumber != '':
                return versionNumber
        except (InvalidPlistException, NotBinaryPlistException) as e:
            return '1.0'
		"""
        return '1.0'

    def setCocosPlayMode(self, isCocosPlay):
        """set apk is cocosplay"""
        self.__isCocosPlayMode = isCocosPlay

    def isCocosPlayMode(self):
        return self.__isCocosPlayMode
