INCLUDES= -I$(top_srcdir)/include $(OGREAL_CFLAGS) $(OIS_CFLAGS)
demosdir= $(abs_top_builddir)/Demos/bin
demos_PROGRAMS= Doppler
Doppler_SOURCES= Listener.cpp  Listener.h  main.cpp  OgreApp.cpp  OgreApp.h BetaGUI.h BetaGUI.cpp
Doppler_LDFLAGS= -L$(top_builddir)/src
Doppler_LDADD= -lOgreAL $(OIS_LIBS)
