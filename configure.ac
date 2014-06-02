AC_PREREQ(2.50)

AC_INIT([OgreAL], [0.2])
AM_INIT_AUTOMAKE([OgreAL], [0.2])
AC_CONFIG_HEADERS([include/config.h])

dnl Check for programs
AC_PROG_CC
AC_PROG_CXX
AM_PROG_CC_C_O
AC_PROG_INSTALL

dnl Generate dymamic libraries only
AC_DISABLE_STATIC
AC_PROG_LIBTOOL

dnl Checking for Ogre 'Dagon'
OGRE_VERSION=1.2
PKG_CHECK_MODULES(OGRE, OGRE >= $OGRE_VERSION)

dnl Checking for vorbisfile since it requires vorbis and ogg
PKG_CHECK_MODULES(VORBIS, vorbisfile)

dnl Chekcing for OpenAL
PKG_CHECK_MODULES(OPENAL, openal)

dnl The Demos require OIS
PKG_CHECK_MODULES(OIS, OIS)

dnl You may want to export each var individually
AC_SUBST(OGREAL_CFLAGS,"$OGRE_CFLAGS $VORBIS_FLAGS $OPENAL_FLAGS")
AC_SUBST(OGREAL_LIBS, "$OGRE_LIBS $VORBIS_LIBS $OPENAL_LIBS")

dnl Paths for demos
demoexecdir='${abs_top_builddir}/Demos/bin'
AC_SUBST(abs_top_builddir)
AC_SUBST(OGRE_PLUGINDIR, [$($PKG_CONFIG --variable=plugindir OGRE)])
AC_SUBST(demoexecdir)

AC_CONFIG_FILES([ \
    Makefile \
    include/Makefile \
    src/Makefile \
    Demos/Makefile \
    Demos/bin/Makefile \
    Demos/Basic_Demo/Makefile \
    Demos/Directional_Demo/Makefile \
    Demos/Doppler_Demo/Makefile \
    Demos/ManySources_Demo/Makefile \
    Demos/MultiChannel_Demo/Makefile \
    Demos/PlayPen/Makefile \
    OgreAL.pc])

AC_OUTPUT
