APPNAME="opensdk"

# paths

if [ -z "${NDK_ROOT+aaa}" ];then
echo "please define NDK_ROOT"
exit 1
fi

DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )"
# ... use paths relative to current directory

OPENSDK_ROOT="$DIR/.."
OPENSDK_ANDROID_ROOT="$DIR"

echo "NDK_ROOT = $NDK_ROOT"
echo "OPENSDK_ROOT = $OPENSDK_ROOT"
echo "OPENSDK_ANDROID_ROOT = $OPENSDK_ANDROID_ROOT"


# run ndk-build
"$NDK_ROOT"/ndk-build -C "$OPENSDK_ANDROID_ROOT" $*