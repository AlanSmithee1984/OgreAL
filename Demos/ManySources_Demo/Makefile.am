INCLUDES= -I$(top_srcdir)/include $(OGREAL_CFLAGS) $(OIS_CFLAGS)
demosdir= $(abs_top_builddir)/Demos/bin
demos_PROGRAMS= ManySources
ManySources_SOURCES= Listener.cpp  Listener.h  main.cpp  OgreApp.cpp  OgreApp.h
ManySources_LDFLAGS= -L$(top_builddir)/src
ManySources_LDADD= -lOgreAL $(OIS_LIBS) 