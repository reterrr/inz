#!/bin/bash

mkdir -p generated/lexer generated/parser

python script.py tokens/tokens.yml \
  --template-dir=templates --out-dir=generated