#include <gio/gio.h>

#if defined (__ELF__) && ( __GNUC__ > 2 || (__GNUC__ == 2 && __GNUC_MINOR__ >= 6))
# define SECTION __attribute__ ((section (".gresource.base_gresource"), aligned (sizeof(void *) > 8 ? sizeof(void *) : 8)))
#else
# define SECTION
#endif

static const SECTION union { const guint8 data[685]; const double alignment; void * const ptr;}  base_gresource_resource_data = {
  "\107\126\141\162\151\141\156\164\000\000\000\000\000\000\000\000"
  "\030\000\000\000\164\000\000\000\000\000\000\050\003\000\000\000"
  "\000\000\000\000\001\000\000\000\002\000\000\000\321\324\220\013"
  "\002\000\000\000\164\000\000\000\004\000\166\000\170\000\000\000"
  "\041\001\000\000\317\271\024\341\002\000\000\000\041\001\000\000"
  "\012\000\166\000\060\001\000\000\242\002\000\000\324\265\002\000"
  "\377\377\377\377\242\002\000\000\001\000\114\000\244\002\000\000"
  "\254\002\000\000\162\056\152\163\263\000\000\000\001\000\000\000"
  "\170\332\065\216\101\016\202\060\020\105\327\160\012\062\253\066"
  "\061\275\000\161\243\222\210\221\270\320\013\124\146\040\215\060"
  "\065\355\040\022\343\335\005\215\253\377\362\376\342\177\364\365"
  "\320\023\213\261\210\305\143\206\243\213\102\114\101\301\356\124"
  "\155\075\313\342\274\105\102\130\065\003\327\342\074\053\375\112"
  "\223\321\061\372\321\214\164\275\071\061\075\305\150\133\332\133"
  "\306\216\102\064\201\054\116\346\356\243\124\277\106\301\127\201"
  "\316\323\004\377\243\055\111\321\321\202\233\251\104\005\102\117"
  "\001\155\034\317\007\056\063\257\063\130\042\153\202\357\263\303"
  "\031\362\364\255\363\017\031\174\077\251\000\050\165\165\141\171"
  "\051\151\156\144\145\170\056\150\164\155\154\000\000\000\000\000"
  "\061\002\000\000\001\000\000\000\170\332\155\122\301\156\333\060"
  "\014\075\327\137\241\351\022\240\230\354\005\275\024\211\345\113"
  "\332\141\267\025\150\173\330\221\225\351\230\003\055\271\026\235"
  "\324\373\372\311\366\122\024\350\240\203\104\276\107\076\076\111"
  "\345\227\273\237\207\247\137\017\367\252\225\216\253\254\234\067"
  "\305\340\217\126\243\327\163\002\241\256\262\054\273\052\073\024"
  "\120\256\205\041\242\130\075\112\143\156\165\121\135\200\126\244"
  "\067\370\072\322\311\352\103\360\202\136\314\043\272\161\040\231"
  "\314\103\140\162\223\126\156\005\254\256\261\201\221\305\304\301"
  "\251\115\104\156\066\252\006\201\335\322\046\356\212\042\106\316"
  "\217\121\100\310\345\056\164\152\063\372\010\015\032\074\001\157"
  "\366\052\312\304\370\261\372\202\223\147\362\230\030\035\326\004"
  "\013\343\172\257\250\073\176\226\372\067\314\156\077\273\310\256"
  "\226\365\037\243\317\117\337\223\321\167\237\036\072\264\372\104"
  "\170\356\303\040\037\054\235\251\226\326\326\170\042\207\146\011"
  "\276\052\362\044\004\154\242\003\106\273\315\277\055\175\204\204"
  "\261\272\013\156\354\122\145\131\254\161\002\242\033\250\027\225"
  "\046\265\172\310\177\107\135\225\305\232\113\017\121\254\057\121"
  "\276\204\172\232\311\311\323\312\274\134\231\043\146\114\112\371"
  "\333\364\247\240\016\216\030\013\007\003\207\150\342\031\137\114"
  "\077\204\206\030\363\164\356\227\071\332\155\365\003\231\203\202"
  "\324\174\273\144\156\024\325\126\013\276\311\254\335\336\314\272"
  "\253\140\212\346\037\362\027\164\310\265\333\000\050\165\165\141"
  "\171\051\057\000\001\000\000\000\000\000\000\000" };

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
