#!/bin/bash

export RRS_DEV_ROOT=/home/${USER}/work/Projects/RRS/RRS-1.6.0

cp -r ../../modules/* ${RRS_DEV_ROOT}/modules
cp -r ../cfg/* ${RRS_DEV_ROOT}/cfg
cp -r ../data/* ${RRS_DEV_ROOT}/data