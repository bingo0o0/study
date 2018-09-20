#! /usr/bin/env bash

#apt-add-repository    apt-config            apt-get               apt-sortpkgs
#apt-cache             apt-extracttemplates  apt-key               
#apt-cdrom             apt-ftparchive        apt-mar


APT_GET_CMD="help update upgrade install remove autoremove purge source build-dev
			dist-upgrade dselect-upgrade clean autoclean check changelog download"


_apt_get()
{
	COMPREPLY=();
	local cur=${COMP_WORDS[$COMP_CWORD]};
	local cmd=${COMP_WORDS[$COMP_CWORD-1]};

	case $cmd in
	'apt-get')
		COMPREPLY=( $(compgen -W "${APT_GET_CMD}" -- $cur) );;
	'*')
		;;
	esac

	return 0;
}



complete -F _apt_get apt-get
