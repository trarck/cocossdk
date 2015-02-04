import threading

class ConfigParse(object):
    """The class can parse project config file of xml """

    def __init__(self):
        """disable the __init__ method"""
        pass

    __config_parse = None
    __lock = threading.Lock()
    _output_dir = ''

    @staticmethod
    def share_instance():
        ConfigParse.__lock.acquire()
        if not ConfigParse.__config_parse:
            ConfigParse.__config_parse = object.__new__(ConfigParse)
            object.__init__(ConfigParse.__config_parse)
            ConfigParse.__config_parse.project_config_init()
        ConfigParse.__lock.release()
        return ConfigParse.__config_parse

    def project_config_init(self):
        """Read config.xml file and save to a dictionary"""
        #self.initDatabase()

    def get_output_dir(self):
        return self._output_dir