INCLUDES= -I$(top_srcdir)/include $(OGREAL_CFLAGS) $(OIS_CFLAGS)
demosdir= $(abs_top_builddir)/Demos/bin
demos_PROGRAMS= MultiChannel
MultiChannel_SOURCES= Listener.cpp  Listener.h  main.cpp  OgreApp.cpp  OgreApp.h
MultiChannel_LDFLAGS= -L$(top_builddir)/src
MultiChannel_LDADD= -lOgreAL $(OIS_LIBS)
