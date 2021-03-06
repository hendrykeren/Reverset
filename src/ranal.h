#ifndef _R_ANAL_H
#define _R_ANAL_H

#include "rdis.h"
#include "rfile.h"
#include "arch/x86_64/x64lift.h"
#include "rmeta.h"
#include "arch/x86common.h"
#include "rinfo.h"
#include "rbb.h"
#include "dec/ssa.h"

static char * unix64_cc[] = {
	"rdi",
	"rsi",
	"rdx",
	"rcx",
	"r8",
	"r9",
	"stk"
};

typedef struct r_analyzer
{
	ril_operation_table *table;
	int function;

	r_function * functions;
	int num_functions;

	r_branch * branches;
	int num_branches;
} r_analyzer;

/*Analyzes metadata, instructions, and file data to form comments, xrefs, data sections and more*/
r_analyzer * r_analyzer_init();
void r_analyzer_destroy(r_analyzer * anal);

void r_meta_auto(r_analyzer * anal, r_disassembler * disassembler, r_file * file);
void r_meta_analyze(r_analyzer * anal, r_disassembler * disassembler, r_file * file);

void r_meta_calculate_branches(r_analyzer * anal, r_disassembler * disassembler);

void r_meta_rip_resolve(r_disassembler * disassembler, r_file * file);
void r_meta_reloc_resolve(r_disassembler * disassembler, r_file * file);

void r_meta_symbol_replace(r_disassembler * disassembler, r_file * file);
void r_meta_string_replace(r_disassembler * disassembler, r_file * file);
void r_meta_func_replace(r_disassembler * disassembler, r_file * file, r_analyzer * anal);
void r_meta_find_xrefs(r_disassembler * disassembler, r_file * file);

uint64_t r_meta_get_address(char * operand, int * status);
int r_meta_isaddr(char * operand, int * len);
int r_meta_rip_relative(char * operand);
int r_meta_indirect_address(char * operand);
r_disasm *r_meta_find_disas(r_disassembler *disassembler, uint64_t address);
r_disasm *r_meta_find_recursive(r_disassembler *disassembler, uint64_t a, int s, int e);
void r_add_xref(r_disasm * to, r_disasm * from, int type);

void r_meta_func_analyze(r_disassembler *disassembler,r_file *file,r_analyzer *anal,int sidx);
/*Very Rudimentary Argument Recognition by using the current ABI's calling convention*/
void r_function_arguments(r_disassembler * disassembler, r_analyzer * anal, r_function * func, r_abi abi);
void r_function_arg_replacer(r_disassembler * disassembler, int idx, r_function * func, r_abi abi);
int r_function_get_stack_args(char * operand, r_abi abi);
int r_function_get_stack_locals(char * operand, r_abi abi);

/*Local Naming through finding stack offsets*/
void r_function_locals(r_disassembler * disassembler, r_function * func, r_abi abi);

#endif
