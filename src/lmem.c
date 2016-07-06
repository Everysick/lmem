#include "lmem.h"

// collapse
static mrb_value
mrb_collapse_init(mrb_state *mrb, mrb_value self)
{
	struct collapse *col;

	col = (struct collapse *)mrb_malloc(mrb, sizeof(struct collapse));

	struct RClass *bal = mrb_class_get(mrb, "Balance");
	mrb_value cv = mrb_obj_value(bal);
	mrb_value arg_value = mrb_fixnum_value(100);
	col->bal = mrb_funcall(mrb, cv, "new", 1, arg_value);

	DATA_TYPE(self) = &mrb_collapse_type;
	DATA_PTR(self) = col;

	return self;
}

static void
mrb_collapse_free(mrb_state *mrb, void *ptr)
{
	struct collapse *col = ptr;
	fprintf(stdout, "FREE COLLAPSE\n");
	mrb_free(mrb, col);
}

static mrb_value
mrb_collapse_balance(mrb_state *mrb, mrb_value self)
{
	struct collapse *col;
	col = DATA_PTR(self);

	return col->bal;
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


// balance
static mrb_value
mrb_balance_init(mrb_state *mrb, mrb_value self)
{
	struct balance *bal;
	mrb_int num;

	bal = (struct balance *)mrb_malloc(mrb, sizeof(struct balance));

	mrb_get_args(mrb, "i", &num);
	bal->num = num;

	DATA_TYPE(self) = &mrb_balance_type;
	DATA_PTR(self) = bal;

	return self;
}

static void
mrb_balance_free(mrb_state *mrb, void *ptr)
{
	struct balance *bal = ptr;
	fprintf(stdout, "FREE BALANCE: %d\n", bal->num);
	mrb_free(mrb, bal);
}

static mrb_value
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

void
mrb_lmem_gem_init(mrb_state *mrb)
{
	struct RClass *col, *bal;

	col = mrb_define_class(mrb, "Collapse", mrb->object_class);
	MRB_SET_INSTANCE_TT(col, MRB_TT_DATA);
	mrb_define_method(mrb, col, "initialize", mrb_collapse_init, MRB_ARGS_NONE());
	mrb_define_method(mrb, col, "initialize_copy", mrb_collapse_init_copy, MRB_ARGS_NONE());
	mrb_define_method(mrb, col, "balance", mrb_collapse_balance, MRB_ARGS_NONE());

	bal = mrb_define_class(mrb, "Balance", mrb->object_class);
	MRB_SET_INSTANCE_TT(bal, MRB_TT_DATA);
	mrb_define_method(mrb, bal, "initialize", mrb_balance_init, MRB_ARGS_REQ(1));
	mrb_define_method(mrb, bal, "initialize_copy", mrb_balance_init_copy, MRB_ARGS_NONE());
	mrb_define_method(mrb, bal, "number", mrb_balance_get, MRB_ARGS_NONE());

	return;
}

void
mrb_lmem_gem_final(mrb_state *mrb)
{
	return;
}
