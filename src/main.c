#include <stdio.h>
#include <alloca.h>
#include <assert.h>

#define COP_FUN(f) f { cop_list scope; cop_list_init(&scope); cop_list* top = &scope;

#define COP_OBJECT(o, name, ...) o name = o##_def; \
	COP_DBGPRINT("ctor: %p; dtor: %p; ctx: %p\n", name.ctor ##_ ##o, name.dtor ##_ ##o, &name); \
	name.ctor ##_ ##o(&name, ##__VA_ARGS__); \
	top->dtor = name.dtor ##_ ##o; \
	top->ctx = &name; \
	top->next = alloca (sizeof (cop_list)); \
	cop_list_init(top->next); \
	top = top->next;

#define COP_NEW(o)

#define END cop_scope_free(&scope); }

#ifdef COP_DBG
	#define COP_DBGPRINT(fmt, ...) printf(fmt, __VA_ARGS__);
#else
	#define COP_DBGPRINT(fmt, ...) 
#endif

#define COP_RET(value) cop_scope_free (&scope); return (value);

typedef struct cop_list
{
	void* ctx;
	void (*dtor)(void* ctx);
	struct cop_list* next;
} cop_list;

void cop_list_init(cop_list* list)
{
	list->ctx = NULL;
	list->dtor = NULL;
	list->next = NULL;
}

void cop_def_ctor(void* d)
{
	COP_DBGPRINT("%s; ctx: %p\n", "ctor call", d);
}

void cop_def_dtor(void* d)
{
	COP_DBGPRINT("%s; ctx: %p\n", "dtor call", d);
}

#define COP_CLASS(cl) \
	void null ##_ ##cl ##_impl () { printf("%s\n", "Not yet implemented method."); }\
	struct cl \
	{ \
	struct 

#define DECL_SPECIAL(cl, name, ...) \
	void (* name ##_ ##cl )(struct cl* this, ##__VA_ARGS__ );

#define COP_CLASS_END(cl) ; void* data; }; \
	typedef struct cl cl; 

#define _IMPL_(cl,name) name ##_ ##cl ##_impl

#define IMPL_SPECIAL(cl, name, ...) void _IMPL_(cl, name) (struct cl* this, ##__VA_ARGS__) 

#define CCAT(arg1, arg2)   arg1##arg2

#define COP_BIND_FUN_1(cl, fun, ...) &_IMPL_(cl, fun)
#define COP_BIND_FUN_2(cl, fun, ...) &_IMPL_(cl, fun), COP_BIND_FUN_1(cl, __VA_ARGS__)
#define COP_BIND_FUN_3(cl, fun, ...) &_IMPL_(cl, fun), COP_BIND_FUN_2(cl, __VA_ARGS__)
#define COP_BIND_FUN_4(cl, fun, ...) &_IMPL_(cl, fun), COP_BIND_FUN_3(cl, __VA_ARGS__)
#define COP_BIND_FUN_5(cl, fun, ...) &_IMPL_(cl, fun), COP_BIND_FUN_4(cl, __VA_ARGS__)
#define COP_BIND_FUN_6(cl, fun, ...) &_IMPL_(cl, fun), COP_BIND_FUN_5(cl, __VA_ARGS__)
#define COP_BIND_FUN_7(cl, fun, ...) &_IMPL_(cl, fun), COP_BIND_FUN_6(cl, __VA_ARGS__)
#define COP_BIND_FUN_8(cl, fun, ...) &_IMPL_(cl, fun), COP_BIND_FUN_7(cl, __VA_ARGS__)

#define VA_NARGS_IMPL(_0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, N, ...) N
#define VA_NARGS(...) VA_NARGS_IMPL(_, ## __VA_ARGS__, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1, 0)

#define COP_BIND_FUN_(N, cl, fun, ...) CCAT(COP_BIND_FUN_, N)(cl, fun, __VA_ARGS__)

#define COP_BIND_FUN(cl, ...) COP_BIND_FUN_(VA_NARGS(__VA_ARGS__), cl, __VA_ARGS__)

#define BIND_IMPL(cl, ...) cl cl ##_def = { COP_BIND_FUN (cl, __VA_ARGS__) };

COP_CLASS (cop_object)
{
	DECL_SPECIAL (cop_object, ctor, int x)
	DECL_SPECIAL (cop_object, dtor)
} 
COP_CLASS_END(cop_object)

IMPL_SPECIAL (cop_object, ctor, int x)
{
	COP_DBGPRINT("%s\n", "ctor impl call");
}

BIND_IMPL (cop_object, ctor, null)

void cop_scope_free (cop_list* scope)
{
	COP_DBGPRINT ("%s; dtor: %p; next: %p\n", "scope freeing call", scope->dtor, scope->next);
	if (scope->dtor)
		scope->dtor(scope->ctx);
	
	if (scope->next)
		cop_scope_free(scope->next);
}

COP_FUN ( void call() )
{
	printf("%s\n", "call to call()");
} END

COP_FUN( int main() )
{
	COP_OBJECT(cop_object, bro, 0);
	COP_RET (0);
} END
