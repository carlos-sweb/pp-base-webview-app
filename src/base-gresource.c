#include <gio/gio.h>

#if defined (__ELF__) && ( __GNUC__ > 2 || (__GNUC__ == 2 && __GNUC_MINOR__ >= 6))
# define SECTION __attribute__ ((section (".gresource.base_gresource"), aligned (sizeof(void *) > 8 ? sizeof(void *) : 8)))
#else
# define SECTION
#endif

static const SECTION union { const guint8 data[777]; const double alignment; void * const ptr;}  base_gresource_resource_data = {
  "\107\126\141\162\151\141\156\164\000\000\000\000\000\000\000\000"
  "\030\000\000\000\164\000\000\000\000\000\000\050\003\000\000\000"
  "\000\000\000\000\001\000\000\000\002\000\000\000\321\324\220\013"
  "\002\000\000\000\164\000\000\000\004\000\166\000\170\000\000\000"
  "\047\001\000\000\317\271\024\341\002\000\000\000\047\001\000\000"
  "\012\000\166\000\070\001\000\000\377\002\000\000\324\265\002\000"
  "\377\377\377\377\377\002\000\000\001\000\114\000\000\003\000\000"
  "\010\003\000\000\162\056\152\163\272\000\000\000\001\000\000\000"
  "\170\332\065\216\101\016\202\060\020\105\327\162\012\062\053\232"
  "\230\036\000\342\106\045\121\042\141\241\027\250\314\100\032\141"
  "\152\332\101\044\306\273\013\032\127\377\345\375\305\377\350\352"
  "\241\047\026\155\020\363\307\014\047\033\204\230\174\002\373\252"
  "\334\071\226\305\071\203\204\260\156\006\256\305\072\116\324\053"
  "\132\215\226\321\215\172\244\353\315\212\356\051\004\323\322\301"
  "\060\166\344\203\366\144\160\322\167\027\244\374\065\011\174\025"
  "\250\054\132\341\177\264\045\311\073\132\160\073\035\061\001\241"
  "\247\200\322\226\347\003\227\231\067\061\054\021\067\336\365\161"
  "\161\116\323\264\250\212\012\262\350\255\262\017\340\176\101\211"
  "\000\050\165\165\141\171\051\151\156\144\145\170\056\150\164\155"
  "\154\000\000\000\000\000\000\000\271\002\000\000\001\000\000\000"
  "\170\332\145\122\301\116\344\060\014\075\317\174\205\311\145\244"
  "\325\246\145\064\053\204\146\332\136\140\021\007\044\020\014\207"
  "\075\172\123\117\033\224\046\335\306\051\364\357\111\332\005\041"
  "\321\113\152\077\307\176\357\071\305\331\365\375\325\361\317\303"
  "\157\150\271\063\325\272\110\007\030\264\115\051\310\212\224\040"
  "\254\253\365\252\350\210\021\124\213\203\047\056\105\340\223\274"
  "\024\171\002\316\244\134\300\226\271\227\364\057\350\261\024\127"
  "\316\062\131\226\117\244\302\240\171\222\017\316\150\065\011\120"
  "\013\120\212\232\116\030\014\113\077\050\330\170\062\247\015\324"
  "\310\270\237\333\370\175\236\173\157\262\306\063\262\126\231\162"
  "\035\154\202\365\170\042\111\043\232\315\001\074\117\206\276\336"
  "\376\300\265\065\332\122\254\350\250\326\070\127\374\070\200\356"
  "\232\357\243\376\223\331\037\242\222\225\224\337\145\076\037\157"
  "\242\314\317\274\305\216\112\061\152\172\355\335\300\137\304\274"
  "\352\232\333\262\246\121\053\222\163\360\023\264\325\254\321\110"
  "\257\320\120\271\315\316\347\076\254\331\120\165\355\124\350\342"
  "\315\042\137\342\010\170\065\350\236\041\162\054\305\220\275\170"
  "\121\025\371\222\213\113\310\227\055\024\177\135\075\125\253\165"
  "\054\037\165\115\156\046\060\070\343\001\003\273\336\340\004\013"
  "\023\161\361\353\134\100\113\272\151\043\273\335\105\232\015\120"
  "\170\027\006\105\313\214\017\233\137\320\006\057\171\224\275\231"
  "\062\117\026\153\227\051\223\247\146\106\173\376\374\311\272\135"
  "\270\024\300\123\037\055\300\276\217\353\214\253\161\066\177\223"
  "\135\117\315\363\343\335\074\343\030\242\113\043\065\261\315\000"
  "\326\201\167\311\052\204\205\357\355\335\123\026\325\314\101\025"
  "\145\104\041\355\266\272\045\143\034\140\374\242\320\155\062\243"
  "\335\201\256\113\301\364\306\311\207\166\227\074\230\305\047\057"
  "\322\113\175\007\153\321\344\060\000\050\165\165\141\171\051\057"
  "\001\000\000\000\000\000\000\000" };

static GStaticResource static_resource = { base_gresource_resource_data.data, sizeof (base_gresource_resource_data.data) - 1 /* nul terminator */, NULL, NULL, NULL };

G_MODULE_EXPORT
GResource *base_gresource_get_resource (void);
GResource *base_gresource_get_resource (void)
{
  return g_static_resource_get_resource (&static_resource);
}
/* GLIB - Library of useful routines for C programming
 * Copyright (C) 1995-1997  Peter Mattis, Spencer Kimball and Josh MacDonald
 *
 * SPDX-License-Identifier: LGPL-2.1-or-later
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.	 See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, see <http://www.gnu.org/licenses/>.
 */

/*
 * Modified by the GLib Team and others 1997-2000.  See the AUTHORS
 * file for a list of people on the GLib Team.  See the ChangeLog
 * files for a list of changes.  These files are distributed with
 * GLib at ftp://ftp.gtk.org/pub/gtk/.
 */

#ifndef __G_CONSTRUCTOR_H__
#define __G_CONSTRUCTOR_H__

/*
  If G_HAS_CONSTRUCTORS is true then the compiler support *both* constructors and
  destructors, in a usable way, including e.g. on library unload. If not you're on
  your own.

  Some compilers need #pragma to handle this, which does not work with macros,
  so the way you need to use this is (for constructors):

  #ifdef G_DEFINE_CONSTRUCTOR_NEEDS_PRAGMA
  #pragma G_DEFINE_CONSTRUCTOR_PRAGMA_ARGS(my_constructor)
  #endif
  G_DEFINE_CONSTRUCTOR(my_constructor)
  static void my_constructor(void) {
   ...
  }

*/

#ifndef __GTK_DOC_IGNORE__

#if  __GNUC__ > 2 || (__GNUC__ == 2 && __GNUC_MINOR__ >= 7)

#define G_HAS_CONSTRUCTORS 1

#define G_DEFINE_CONSTRUCTOR(_func) static void __attribute__((constructor)) _func (void);
#define G_DEFINE_DESTRUCTOR(_func) static void __attribute__((destructor)) _func (void);

#elif defined (_MSC_VER)

/*
 * Only try to include gslist.h if not already included via glib.h,
 * so that items using gconstructor.h outside of GLib (such as
 * GResources) continue to build properly.
 */
#ifndef __G_LIB_H__
#include "gslist.h"
#endif

#include <stdlib.h>

#define G_HAS_CONSTRUCTORS 1

/* We do some weird things to avoid the constructors being optimized
 * away on VS2015 if WholeProgramOptimization is enabled. First we
 * make a reference to the array from the wrapper to make sure its
 * references. Then we use a pragma to make sure the wrapper function
 * symbol is always included at the link stage. Also, the symbols
 * need to be extern (but not dllexport), even though they are not
 * really used from another object file.
 */

/* We need to account for differences between the mangling of symbols
 * for x86 and x64/ARM/ARM64 programs, as symbols on x86 are prefixed
 * with an underscore but symbols on x64/ARM/ARM64 are not.
 */
#ifdef _M_IX86
#define G_MSVC_SYMBOL_PREFIX "_"
#else
#define G_MSVC_SYMBOL_PREFIX ""
#endif

#define G_DEFINE_CONSTRUCTOR(_func) G_MSVC_CTOR (_func, G_MSVC_SYMBOL_PREFIX)
#define G_DEFINE_DESTRUCTOR(_func) G_MSVC_DTOR (_func, G_MSVC_SYMBOL_PREFIX)

#define G_MSVC_CTOR(_func,_sym_prefix) \
  static void _func(void); \
  extern int (* _array ## _func)(void);              \
  int _func ## _wrapper(void);              \
  int _func ## _wrapper(void) { _func(); g_slist_find (NULL,  _array ## _func); return 0; } \
  __pragma(comment(linker,"/include:" _sym_prefix # _func "_wrapper")) \
  __pragma(section(".CRT$XCU",read)) \
  __declspec(allocate(".CRT$XCU")) int (* _array ## _func)(void) = _func ## _wrapper;

#define G_MSVC_DTOR(_func,_sym_prefix) \
  static void _func(void); \
  extern int (* _array ## _func)(void);              \
  int _func ## _constructor(void);              \
  int _func ## _constructor(void) { atexit (_func); g_slist_find (NULL,  _array ## _func); return 0; } \
   __pragma(comment(linker,"/include:" _sym_prefix # _func "_constructor")) \
  __pragma(section(".CRT$XCU",read)) \
  __declspec(allocate(".CRT$XCU")) int (* _array ## _func)(void) = _func ## _constructor;

#elif defined(__SUNPRO_C)

/* This is not tested, but i believe it should work, based on:
 * http://opensource.apple.com/source/OpenSSL098/OpenSSL098-35/src/fips/fips_premain.c
 */

#define G_HAS_CONSTRUCTORS 1

#define G_DEFINE_CONSTRUCTOR_NEEDS_PRAGMA 1
#define G_DEFINE_DESTRUCTOR_NEEDS_PRAGMA 1

#define G_DEFINE_CONSTRUCTOR_PRAGMA_ARGS(_func) \
  init(_func)
#define G_DEFINE_CONSTRUCTOR(_func) \
  static void _func(void);

#define G_DEFINE_DESTRUCTOR_PRAGMA_ARGS(_func) \
  fini(_func)
#define G_DEFINE_DESTRUCTOR(_func) \
  static void _func(void);

#else

/* constructors not supported for this compiler */

#endif

#endif /* __GTK_DOC_IGNORE__ */
#endif /* __G_CONSTRUCTOR_H__ */

#ifdef G_HAS_CONSTRUCTORS

#ifdef G_DEFINE_CONSTRUCTOR_NEEDS_PRAGMA
#pragma G_DEFINE_CONSTRUCTOR_PRAGMA_ARGS(base_gresourceresource_constructor)
#endif
G_DEFINE_CONSTRUCTOR(base_gresourceresource_constructor)
#ifdef G_DEFINE_DESTRUCTOR_NEEDS_PRAGMA
#pragma G_DEFINE_DESTRUCTOR_PRAGMA_ARGS(base_gresourceresource_destructor)
#endif
G_DEFINE_DESTRUCTOR(base_gresourceresource_destructor)

#else
#warning "Constructor not supported on this compiler, linking in resources will not work"
#endif

static void base_gresourceresource_constructor (void)
{
  g_static_resource_init (&static_resource);
}

static void base_gresourceresource_destructor (void)
{
  g_static_resource_fini (&static_resource);
}
