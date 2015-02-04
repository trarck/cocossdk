import sys, string, os
from xml.etree import ElementTree as ET
import re
import my_util
from xml.dom import minidom
import codecs

_android_ns = 'http://schemas.android.com/apk/res/android'

def do_modify(manifest_file, source_file, root):
    """
        modify AndroidManifest.xml by ForManifest.xml
    """
    if not os.path.exists(manifest_file):
        return False
    if not os.path.exists(source_file):
        return False
    ret = False
    source_tree = ET.parse(source_file)
    source_root = source_tree.getroot()
    f = open(manifest_file)
    target_content = f.read()
    f.close()
    app_cfg_node = source_root.find('applicationCfg')
    if app_cfg_node is not None and len(app_cfg_node) > 0:
        app_key_word = app_cfg_node.get('keyword')
        my_util.printf('in modify key'+app_key_word)
        if app_key_word != None and len(app_key_word) > 0:
            key_index = target_content.find(app_key_word)
            if -1 == key_index:
                ret = True
                for node in list(app_cfg_node):
                    root.find('application').append(node)

    permission_cfg_node = source_root.find('permissionCfg')
    if permission_cfg_node is not None and len(permission_cfg_node) > 0:
        for one_node in list(permission_cfg_node):
            key = '{' + _android_ns + '}name'
            per_attr = one_node.get(key)
            if per_attr != None and len(per_attr) > 0:
                attr_index = target_content.find(per_attr)
                if -1 == attr_index:
                    ret = True
                    root.append(one_node)
    return ret


def modify(manifest_file, source_config_file, plugin_name, usr_sdk_config):
    manifest_file = my_util.get_full_path(manifest_file)
    source_xml = my_util.get_full_path(source_config_file)
    if not os.path.exists(source_xml):
        for_manifest_dir = os.path.dirname(source_xml)
        screen_orientation = get_orientation(manifest_file, usr_sdk_config)
        if screen_orientation == 'landscape' or screen_orientation == 'auto':
            source_xml = for_manifest_dir + '/ForManifestLandscape.xml'
        else:
            source_xml = for_manifest_dir + '/ForManifestPortrait.xml'
    if not os.path.exists(source_xml):
        return
    ET.register_namespace('android', _android_ns)
    target_tree = ET.parse(manifest_file)
    target_root = target_tree.getroot()
    have_changed = do_modify(manifest_file, source_xml, target_root)
    if have_changed:
        my_util.printf('Modify AndroidManifest.xml for plugin ' + plugin_name)
        target_tree.write(manifest_file, 'UTF-8')


def get_orientation(manifest_file, usr_sdk_config):
    for param in usr_sdk_config['param']:
        if param['name'].count('Orientation') > 0 or param['name'].count('orientation') > 0:
            return param['value']

    if os.path.exists(manifest_file):
        doc = minidom.parse(manifest_file)
        root_node = doc.documentElement
        application_list = root_node.getElementsByTagName('application')
        for application_node in application_list:
            activity_list = root_node.getElementsByTagName('activity')
            for activity_node in activity_list:
                category_list = activity_node.getElementsByTagName('category')
                for category_node in category_list:
                    if category_node.getAttribute('android:name') == 'android.intent.category.LAUNCHER':
                        if activity_node.getAttribute('android:screenOrientation') == 'portrait' or activity_node.getAttribute('android:screenOrientation') == 'landscape':
                            return activity_node.getAttribute('android:screenOrientation')
                        if application_node.getAttribute('android:screenOrientation') == 'portrait' or application_node.getAttribute('android:screenOrientation') == 'landscape':
                            return application_node.getAttribute('android:screenOrientation')

    my_util.printf('Default Orientation')
    return 'landscape'
