SVN_SUB_CMD="add
   auth
   blame
   cat
   changelist
   checkout
   cleanup
   commit
   copy
   delete
   diff
   export
   help
   import
   info
   list
   lock
   log
   merge
   mergeinfo
   mkdir
   move
   patch
   propdel
   propedit
   propget
   proplist
   propset
   relocate
   resolve
   resolved
   revert
   status
   switch
   unlock
   update
   upgrade"


_svn()
{
	COMPREPLY=()
	local cur=${COMP_WORDS[${COMP_CWORD}]}
	local prev=${COMP_WORDS[${COMP_CWORD}-1]}
	
	COMPREPLY=( $(compgen -W "$SVN_SUB_CMD" -- $cur) )
	
	return 0
}


complete -F _svn -A file svn
































