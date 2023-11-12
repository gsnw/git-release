#include "git-compat-util.h"
#include "abspath.h"
#include "base85.h"
#include "convert.h"
#include "environment.h"
#include "gettext.h"
#include "hex.h"
#include "object-store-ll.h"
#include "merge-ll.h"
#include "oid-array.h"
#include "pager.h"
#include "object-file.h"
#include "object-name.h"
#include "read-cache-ll.h"
#include "setup.h"
#include "ws.h"
		string_list_split_in_place(&params, params_copy, ",", -1);
int git_diff_ui_config(const char *var, const char *value,
		       const struct config_context *ctx, void *cb)
		diff_context_default = git_config_int(var, value, ctx->kvi);
		diff_interhunk_context_default = git_config_int(var, value,
								ctx->kvi);
		diff_stat_graph_width = git_config_int(var, value, ctx->kvi);
	return git_diff_basic_config(var, value, ctx, cb);
int git_diff_basic_config(const char *var, const char *value,
			  const struct config_context *ctx, void *cb)
		diff_rename_limit_default = git_config_int(var, value, ctx->kvi);
	return git_default_config(var, value, ctx, cb);
static int count_trailing_blank(mmfile_t *mf)
		if (!ws_blank_line(prev_eol + 1, ptr - prev_eol))
	l1 = count_trailing_blank(mf1);
	l2 = count_trailing_blank(mf2);
	return ws_blank_line(line, len);
				  const char *func UNUSED, long funclen UNUSED)
				    number_width, "Unmerged\n");
static void conclude_dirstat(struct diff_options *options,
			     struct dirstat_dir *dir,
			     unsigned long changed)
{
	struct dirstat_file *to_free = dir->files;

	if (!changed) {
		/* This can happen even with many files, if everything was renames */
		;
	} else {
		/* Show all directories with more than x% of the changes */
		QSORT(dir->files, dir->nr, dirstat_compare);
		gather_dirstat(options, dir, changed, "", 0);
	}

	free(to_free);
}

	conclude_dirstat(options, &dir, changed);
	conclude_dirstat(options, &dir, changed);
				   long ob UNUSED, long on UNUSED,
				   long nb, long nn UNUSED,
				   const char *func UNUSED, long funclen UNUSED)
void diff_set_noprefix(struct diff_options *options)
{
	options->a_prefix = options->b_prefix = "";
}

void diff_set_default_prefix(struct diff_options *options)
{
	options->a_prefix = "a/";
	options->b_prefix = "b/";
}

static int set_diff_algorithm(struct diff_options *opts,
			      const char *alg)
{
	long value = parse_algorithm_value(alg);

	if (value < 0)
		return -1;

	/* clear out previous settings */
	DIFF_XDL_CLR(opts, NEED_MINIMAL);
	opts->xdl_opts &= ~XDF_DIFF_ALGORITHM_MASK;
	opts->xdl_opts |= value;

	return 0;
}

		o->found_changes = 1;
		o->found_changes = 1;
			o->found_changes = 1;
	     reuse_worktree_file(r->index, one->path, &one->oid, 1))) {
		if (lstat(one->path, &st) < 0) {
			die_errno("stat(%s)", one->path);
			if (strbuf_readlink(&sb, one->path, st.st_size) < 0)
				die_errno("readlink(%s)", one->path);
			prep_temp_blob(r->index, one->path, temp, sb.buf, sb.len,
			temp->name = one->path;
		prep_temp_blob(r->index, one->path, temp,
	struct diff_tempfile *temp = prepare_temp_file(r, df);
		add_external_diff_name(o->repo, &cmd.args, one);
		add_external_diff_name(o->repo, &cmd.args, two);
		if (other) {
		return repo_find_unique_abbrev(the_repository, oid, abbrev);
	struct userdiff_driver *drv = NULL;
	if (o->flags.allow_external || !o->ignore_driver_algorithm)

	if (o->flags.allow_external && drv && drv->external)
		pgm = drv->external;
	if (one && two) {
		if (!o->ignore_driver_algorithm && drv && drv->algorithm)
			set_diff_algorithm(o, drv->algorithm);

	} else {
	}
	if (!o->ignore_driver_algorithm) {
		struct userdiff_driver *drv = userdiff_find_by_path(o->repo->index,
								    p->one->path);

		if (drv && drv->algorithm)
			set_diff_algorithm(o, drv->algorithm);
	}

		diff_set_noprefix(options);
		diff_set_default_prefix(options);
int diff_check_follow_pathspec(struct pathspec *ps, int die_on_error)
{
	unsigned forbidden_magic;

	if (ps->nr != 1) {
		if (die_on_error)
			die(_("--follow requires exactly one pathspec"));
		return 0;
	}

	forbidden_magic = ps->items[0].magic & ~(PATHSPEC_FROMTOP |
						 PATHSPEC_LITERAL);
	if (forbidden_magic) {
		if (die_on_error) {
			struct strbuf sb = STRBUF_INIT;
			pathspec_magic_names(forbidden_magic, &sb);
			die(_("pathspec magic not supported by --follow: %s"),
			    sb.buf);
		}
		return 0;
	}

	return 1;
}

	/*
	 * --name-only, --name-status, --checkdiff, and -s
	 * turn other output format off.
	 */
	if (options->flags.follow_renames)
		diff_check_follow_pathspec(&options->pathspec, 1);
	options->output_format &= ~DIFF_FORMAT_NO_OUTPUT;
	options->output_format &= ~DIFF_FORMAT_NO_OUTPUT;
	if (repo_get_oid(the_repository, arg, &oid))
		options->output_format &= ~DIFF_FORMAT_NO_OUTPUT;

	if (set_diff_algorithm(options, arg))
	options->ignore_driver_algorithm = 1;

	return 0;
}

static int diff_opt_diff_algorithm_no_arg(const struct option *opt,
				   const char *arg, int unset)
{
	struct diff_options *options = opt->value;

	BUG_ON_OPT_NEG(unset);
	BUG_ON_OPT_ARG(arg);

	if (set_diff_algorithm(options, opt->long_name))
		BUG("available diff algorithms include \"myers\", "
			       "\"minimal\", \"patience\" and \"histogram\"");

	options->ignore_driver_algorithm = 1;

	diff_set_noprefix(options);
	return 0;
}

static int diff_opt_default_prefix(const struct option *opt,
				   const char *optarg, int unset)
{
	struct diff_options *options = opt->value;

	BUG_ON_OPT_NEG(unset);
	BUG_ON_OPT_ARG(optarg);
	diff_set_default_prefix(options);
	options->ignore_driver_algorithm = 1;

	return set_diff_algorithm(options, "patience");
/*
 * Consider adding new flags to __git_diff_common_options
 * in contrib/completion/git-completion.bash
 */
struct option *add_diff_options(const struct option *opts,
				struct diff_options *options)
		OPT_SET_INT('s', "no-patch", &options->output_format,
			    N_("suppress diff output"), DIFF_FORMAT_NO_OUTPUT),
		OPT_BITOP(0, "raw", &options->output_format,
			  DIFF_FORMAT_RAW, DIFF_FORMAT_NO_OUTPUT),
		OPT_BITOP(0, "numstat", &options->output_format,
			  DIFF_FORMAT_NUMSTAT, DIFF_FORMAT_NO_OUTPUT),
		OPT_BITOP(0, "shortstat", &options->output_format,
			  DIFF_FORMAT_SHORTSTAT, DIFF_FORMAT_NO_OUTPUT),
		OPT_BITOP(0, "summary", &options->output_format,
			  DIFF_FORMAT_SUMMARY, DIFF_FORMAT_NO_OUTPUT),
		OPT_CALLBACK_F(0, "default-prefix", options, NULL,
			       N_("use default prefixes a/ and b/"),
			       PARSE_OPT_NONEG | PARSE_OPT_NOARG, diff_opt_default_prefix),
		OPT_CALLBACK_F(0, "minimal", options, NULL,
			       N_("produce the smallest possible diff"),
			       PARSE_OPT_NONEG | PARSE_OPT_NOARG,
			       diff_opt_diff_algorithm_no_arg),
		OPT_CALLBACK_F(0, "histogram", options, NULL,
			       N_("generate diff using the \"histogram diff\" algorithm"),
			       PARSE_OPT_NONEG | PARSE_OPT_NOARG,
			       diff_opt_diff_algorithm_no_arg),
	return parse_options_concat(opts, parseopts);
	struct option no_options[] = { OPT_END() };
	struct option *parseopts = add_diff_options(no_options, options);

	ac = parse_options(ac, av, prefix, parseopts, NULL,
	free(parseopts);

	opt->found_changes = 1;
	if (output_format & DIFF_FORMAT_PATCH) {
		if (separator) {
			emit_diff_symbol(options, DIFF_SYMBOL_SEPARATOR, NULL, 0, 0);
			if (options->stat_sep)
				/* attach patch instead of inline */
				emit_diff_symbol(options, DIFF_SYMBOL_STAT_SEP,
						 NULL, 0, 0);
		}

		diff_flush_patch_all_file_pairs(options);
	}

	if (output_format & DIFF_FORMAT_CALLBACK)
		options->format_callback(q, options, options->format_callback_data);

	if (options->repo == the_repository && repo_has_promisor_remote(the_repository) &&
int diff_result_code(struct diff_options *opt)

	options->found_changes = !!diffstat->nr;
	temp = prepare_temp_file(r, spec);