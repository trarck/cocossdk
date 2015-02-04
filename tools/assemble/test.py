import os.path
import sys
import traceback
import manifest

def main():
    params={}
    params['param']={}
    manifest.modify('b.xml','a.xml','test',params)

if __name__ == '__main__':
    try:
        main()
    except Exception as e:
        traceback.print_exc()
        sys.exit(1)
