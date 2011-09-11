#!/bin/bash
INPUT="HTTP://google.com/caress/me.html ../i/don?t#thinkso"
EXPECTED="HTTP://google.com/i/don?t#thinkso"
./resolver $INPUT | grep $EXPECTED
