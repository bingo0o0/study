GIT_CMD="add
	bisect
	branch
	checkout
	clone
	commit
	diff
	fetch
	grep
	init
	log
	merge
	mv
	pull
	push
	rebase
	reset
	rm
	show
	status
	tag"


#REMOTE_BRANCH=`git remote`
#WORK_BRANCH=`git branch | grep '*' | sed "s/\* //"`



_git()
{
	COMPREPLY=();
	local cur=${COMP_WORDS[${COMP_CWORD}]};	
	local cmd=${COMP_WORDS[${COMP_CWORD}-1]};

	case $cmd in
	'git')
		COMPREPLY=( $(compgen -W "${GIT_CMD}" -- $cur));;
	'*')
		;;
	esac

	return 0;
}

complete -F _git -A file git








