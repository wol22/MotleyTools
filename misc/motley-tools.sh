#!/bin/sh

# ====================================================================
# 
# --------------------------------------------------------------------

TOOLS=/usr/local/bin/cmassoc

# ====================================================================
# 
# --------------------------------------------------------------------

if [ -d ${TOOLS} ]; then
	export PATH=${PATH}:${TOOLS}:~:.
	echo "Motley Tools are installed!"
	fi

