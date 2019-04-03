
This step is only needed if application intends to use FreeRTOS. It will download pkcs header files from
GitHub website which will be used when building PKCS feature.

  1. Install wget utility (if not already installed)
  2. Open a shell (Linux/cygwin) or command window (windows). Run "sh install_pkcs_headerfiles.sh"
  3. Building QuRT lib and FreeRTOS lib following user guide. "make all" under Linux or "build.bat" under Windows.

