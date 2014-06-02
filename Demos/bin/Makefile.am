EXTRA_DIST = plugins.cfg.in resources.cfg.in
CONFIG_FILES = plugins.cfg resources.cfg

edit = sed \
	-e "s,@OGRE_PLUGINDIR\@,$(OGRE_PLUGINDIR),g" \
	-e "s,@OGREAL_MEDIADIR\@,$(top_srcdir)/Demos/Media,g"

install-data-local:
	for i in $(CONFIG_FILES) ; do \
		$(edit) $(srcdir)/$$i.in > $$i.tmp && \
		$(INSTALL_DATA) $$i.tmp $$i && \
		rm -f $$i.tmp; \
	done

uninstall-local:
	rm -f $(CONFIG_FILES)
