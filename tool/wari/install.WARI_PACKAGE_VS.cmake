# Install Manifest
INSTALL( FILES "${PRE_BUILD_PROJECT_NAME}.exe.manifest"
	DESTINATION bin/
)

# Install dll's
INSTALL(
	DIRECTORY "${EXTERNALS_PATH}/bin/"
	DESTINATION bin
	FILES_MATCHING PATTERN "*.*"
)