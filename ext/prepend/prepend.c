/* (c) 2010 John Mair (banisterfiend), MIT license */

#include "compat.h"
#include "ruby.h"

static VALUE
class_mod_wrapper_to_s(VALUE self)
{
  return rb_iv_get(self, "__class_name__");
}

static VALUE
klass_to_s(VALUE self)
{
  return rb_str_concat(rb_mod_name(self), rb_str_new2("*"));
}

static VALUE
rb_prepend_module(VALUE klass, VALUE module)
{
  /* create module to hold current class's M_TBL */
  VALUE class_mod_wrapper = rb_module_new();

  /* clear the default M_TBL already allocated for new the module */
  st_free_table(RCLASS_M_TBL(class_mod_wrapper));

  /* set the module's M_TBL to the current class's */
  RCLASS_M_TBL(class_mod_wrapper) = RCLASS_M_TBL(klass);

  /* store name of current class in module for use by #to_s and #inspect */
  rb_iv_set(class_mod_wrapper, "__class_name__", rb_mod_name(klass));

  /* set current class's #to_s to return ClassName* */
  rb_define_singleton_method(klass, "to_s", klass_to_s, 0);

  /* set wrapper module #to_s to name of current class */
  rb_define_singleton_method(class_mod_wrapper, "to_s", class_mod_wrapper_to_s, 0);

  /* erase the current class's M_TBL as we're now storing it in the wrapper module */
  RCLASS_M_TBL(klass) = st_init_numtable();
  
  /* include the wrapper module first */
  rb_funcall(klass, rb_intern("include"), 1, class_mod_wrapper);

  /* include the module we want to 'prepend' second, so that it's M_TBL gets precedence over M_TBL of original class
     (NB: original class's M_TBL is now stored in wrapper module) */
  rb_funcall(klass, rb_intern("include"), 1, module);
  
  rb_clear_cache();

  return klass;
}

void
Init_prepend() {
  rb_define_method(rb_cModule, "prepend", rb_prepend_module, 1);
}