#include <stdio.h>
#include <mruby.h>
#include <mruby/class.h>
#include <mruby/value.h>
#include <mruby/data.h>
#include <mruby/array.h>

struct balance
{
	int num;
};

struct collapse
{
	int num;
	struct mrb_value bal;
};

static mrb_value mrb_collapse_init(mrb_state *, mrb_value);
static void mrb_collapse_free(mrb_state *, void *);
static mrb_value mrb_collapse_get(mrb_state *, mrb_value);
static mrb_value mrb_collapse_init_copy(mrb_state *, mrb_value);

static mrb_value mrb_balance_init(mrb_state *, mrb_value);
static void mrb_balance_free(mrb_state *, void *);
static mrb_value mrb_balance_get(mrb_state *, mrb_value);
static mrb_value mrb_balance_init_copy(mrb_state *, mrb_value);

const static struct mrb_data_type mrb_collapse_type = { "Collapse", mrb_collapse_free };
const static struct mrb_data_type mrb_balance_type = { "Balance", mrb_balance_free };
