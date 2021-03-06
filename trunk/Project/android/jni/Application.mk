APP_STL := c++_static
NDK_TOOLCHAIN_VERSION=clang

APP_CPPFLAGS := -frtti -std=c++11 -fsigned-char
APP_LDFLAGS := -latomic


ifeq ($(NDK_DEBUG),1)
  APP_CPPFLAGS += -DCOCOS2D_DEBUG=1
  APP_OPTIM := debug
else
  APP_CPPFLAGS += -DNDEBUG
  APP_OPTIM := release
endif

LOCAL_CFLAGS += \
	-DCC_USE_PHYSICS=0 \
	-DCC_USE_3D_PHYSICS=0 \
	-DCC_ENABLE_BULLET_INTEGRATION=0 \
	-DCC_USE_NAVMESH=0