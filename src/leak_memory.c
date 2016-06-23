#include "mruby.h"
#include "mruby/class.h"
#include "mruby/value.h"
#include "mruby/data.h"

struct collapse {
	int num;
};

struct balance {
	int num;
};

// You should change function from mrb_free to custum dfree
// if you use malloc or fopen.
const static struct mrb_data_type mrb_collapse_type = { "Collapse", mrb_free };
const static struct mrb_data_type mrb_balance_type = { "Balance", mrb_free };

/*
  Collapse class's methods.
*/
mrb_value
mrb_collapse_init(mrb_state *mrb, mrb_value self)
{
	struct collapse *col;

	col = (struct collapse *)mrb_malloc(mrb, sizeof(struct collapse));
	col->num = 1000;

	DATA_TYPE(self) = &mrb_collapse_type;
	DATA_PTR(self) = col;

	return self;
}

mrb_value
mrb_collapse_get(mrb_state *mrb, mrb_value self)
{
	struct collapse *col;
	col = DATA_PTR(self);

	return mrb_fixnum_value(col->num);
}

static mrb_value
mrb_collapse_init_copy(mrb_state *mrb, mrb_value copy)
{
	mrb_value src;
	mrb_get_args(mrb, "o", &src);

	if (mrb_obj_equal(mrb, copy, src)) return copy;

	if (!mrb_obj_is_instance_of(mrb, src, mrb_obj_class(mrb, copy))) {
		mrb_raise(mrb, E_TYPE_ERROR, "wrong argument class");
	}

	if (!DATA_PTR(copy)) {
		DATA_PTR(copy) = (struct collapse *)mrb_malloc(mrb, sizeof(struct collapse));
		DATA_TYPE(copy) = &mrb_collapse_type;
	}

	*(struct collapse *)DATA_PTR(copy) = *(struct collapse *)DATA_PTR(src);
	return copy;
}


/*
  Balance class's methods.
*/
mrb_value
mrb_balance_init(mrb_state *mrb, mrb_value self){

	struct balance *bal;

	bal = (struct balance *)mrb_malloc(mrb, sizeof(struct balance));
	bal->num = 2000;

	DATA_TYPE(self) = &mrb_balance_type;
	DATA_PTR(self) = bal;

	return self;
}

mrb_value
mrb_balance_get(mrb_state *mrb, mrb_value self)
{
	struct balance *bal;
	bal = DATA_PTR(self);

	return mrb_fixnum_value(bal->num);
}

static mrb_value
mrb_balance_init_copy(mrb_state *mrb, mrb_value copy)
{
	mrb_value src;
	mrb_get_args(mrb, "o", &src);

	if (mrb_obj_equal(mrb, copy, src)) return copy;

	if (!mrb_obj_is_instance_of(mrb, src, mrb_obj_class(mrb, copy))) {
		mrb_raise(mrb, E_TYPE_ERROR, "wrong argument class");
	}

	if (!DATA_PTR(copy)) {
		DATA_PTR(copy) = (struct balance *)mrb_malloc(mrb, sizeof(struct balance));
		DATA_TYPE(copy) = &mrb_balance_type;
	}

	*(struct balance *)DATA_PTR(copy) = *(struct balance *)DATA_PTR(src);
	return copy;
}

/*
  Initializer, Finalizer
*/
void
mrb_lmem_gem_init(mrb_state *mrb)
{
	struct RClass *col, *bal;

	// Define struct collapse in mruby
	col = mrb_define_class(mrb, "Collapse", mrb->object_class);
	MRB_SET_INSTANCE_TT(col, MRB_TT_DATA);
	mrb_define_method(mrb, col, "initialize", mrb_collapse_init, MRB_ARGS_NONE());
	mrb_define_method(mrb, col, "initialize_copy", mrb_collapse_init_copy, MRB_ARGS_NONE());
	mrb_define_method(mrb, col, "get_value", mrb_collapse_get, MRB_ARGS_NONE());

	// Define struct balance in mruby
	bal = mrb_define_class(mrb, "Balance", mrb->object_class);
	MRB_SET_INSTANCE_TT(bal, MRB_TT_DATA);
	mrb_define_method(mrb, bal, "initialize", mrb_balance_init, MRB_ARGS_NONE());
	mrb_define_method(mrb, bal, "initialize_copy", mrb_balance_init_copy, MRB_ARGS_NONE());
	mrb_define_method(mrb, bal, "get_value", mrb_balance_get, MRB_ARGS_NONE());

	return;
}

void
mrb_lmem_gem_final(mrb_state *mrb)
{
	return;
}
