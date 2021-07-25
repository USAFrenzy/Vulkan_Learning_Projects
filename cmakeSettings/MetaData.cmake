##################################################################
#                  Simple Meta Data                              #
##################################################################
set(META_PROJECT_NAME    "Vulkan Learning Projects")
set(META_VERSION_MAJOR   "0")
set(META_VERSION_MINOR   "1")
set(META_VERSION_PATCH   "0")
set(META_VERSION         "${META_VERSION_MAJOR}.${META_VERSION_MINOR}.${META_VERSION_PATCH}")
set(META_NAME_VERSION    "${META_PROJECT_NAME} v${META_VERSION} revision(${META_VERSION_REVISION})")

string (MAKE_C_IDENTIFIER ${META_PROJECT_NAME} META_PROJECT_ID)
string(TOUPPER ${META_PROJECT_ID} META_PROJECT_ID)