#pragma  once

/** PASSKEY_STRINGIZE
 *
 * @brief Make a string out of regular text
**/
#define PASSKEY_STRINGIZE(str) IMPL_PASSKEY_STRINGIZE(str)
#define IMPL_PASSKEY_STRINGIZE(str) #str
