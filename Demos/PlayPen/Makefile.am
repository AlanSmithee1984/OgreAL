INCLUDES= -I$(top_srcdir)/include $(OGREAL_CFLAGS) $(OIS_CFLAGS)
demosdir= $(abs_top_builddir)/Demos/bin
demos_PROGRAMS= PlayPen
PlayPen_SOURCES= Listener.cpp  Listener.h  main.cpp  OgreApp.cpp  OgreApp.h
PlayPen_LDFLAGS= -L$(top_builddir)/src
PlayPen_LDADD= -lOgreAL $(OIS_LIBS) 