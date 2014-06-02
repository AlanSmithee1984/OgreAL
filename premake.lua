project.name = "OgreAL"
project.language = "c++"

-- OgreAL
  package = newpackage()
  package.name = "OgreAL"
  package.kind = "dll"
  package.path = "OgreAL"

  package.libdir = "../lib"
  package.bindir = "../lib"
  package.config["Debug"].target = "Debug/OgreAL_d"
  package.config["Release"].target = "Release/OgreAL"
  package.config["Debug"].objdir = "Debug"
  package.config["Release"].objdir = "Release"

  package.defines = {"OGREAL_EXPORT"}
  package.files = {matchfiles("../include/*.h", "../src/*.cpp")}
  package.includepaths = {"$(OGRE_HOME)/OgreMain/include", "../Dependencies/include", "../include"}
  package.config["Debug"].libpaths = {"$(OGRE_HOME)/OgreMain/lib/Debug", "../Dependencies/lib/Win32/Debug"}
  package.config["Release"].libpaths = {"$(OGRE_HOME)/OgreMain/lib/Release", "../Dependencies/lib/Win32/Release"}

  package.links = {"OpenAL32", "ALut"}
  package.config["Debug"].links = {"OgreMain_d", "vorbis_static_d", "vorbisfile_static_d", "ogg_static_d"}
  package.config["Release"].links = {"OgreMain", "vorbis_static", "vorbisfile_static", "ogg_static"}

-- Basic_Demo
  package = newpackage()
  package.name = "Basic_Demo"
  package.kind = "winexe"
  package.path = "Demos/Basic_Demo"

  package.config["Debug"].target = "Debug/Basic_Demo"
  package.config["Release"].target = "Release/Basic_Demo"
  package.config["Debug"].objdir = "Debug"
  package.config["Release"].objdir = "Release"

  package.files = {matchfiles("*.h", "*.cpp")}
  package.includepaths = {"$(OGRE_HOME)/OgreMain/include", "../../Dependencies/include", "../../include"}
  package.config["Debug"].libpaths = {"$(OGRE_HOME)/OgreMain/lib/Debug", "../../Dependencies/lib/Win32/Debug", "../../lib/Debug"}
  package.config["Release"].libpaths = {"$(OGRE_HOME)/OgreMain/lib/Release", "../../Dependencies/lib/Win32/Release", "../../lib/Release"}

  -- Linking to the previous package looks in the wrong path
  -- Looks for ../../OgreAL_d.lib
  package.links = {"OpenAL32", "OgreAL"}
  package.config["Debug"].links = {"OgreMain_d"}
  package.config["Release"].links = {"OgreMain"}
  package.buildflags = {"no-main"}
