SP=" "

test_expect_success 'unknown command' '
	test_when_finished "git reset --hard; rm -f command" &&
	echo W >command &&
	git add -N command &&
	git diff command >expect &&
	cat >>expect <<-EOF &&
	(1/1) Stage addition [y,n,q,a,d,e,p,?]? Unknown command ${SQ}W${SQ} (use ${SQ}?${SQ} for help)
	(1/1) Stage addition [y,n,q,a,d,e,p,?]?$SP
	git add -p -- command <command >actual 2>&1 &&
	test_cmp expect actual
test_expect_success 'reject multi-key input' '
	saved=$(git hash-object -w file) &&
	test_when_finished "git cat-file blob $saved >file" &&
	echo an extra line >>file &&
	test_write_lines aa | git add -p >actual &&
	test_grep "is expected, got ${SQ}aa${SQ}" actual
'
