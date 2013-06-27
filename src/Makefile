##
## Makefile
##
## Copyright (c) 2013 MacGeneration. All rights reserved.
##
## Redistribution and use in source and binary forms, with or without modification, are
## permitted provided that the following conditions are met:
##
## 1. Redistributions of source code must retain the above copyright notice, this list of
## conditions and the following disclaimer.
##
## 2. Redistributions in binary form must reproduce the above copyright notice, this list
## of conditions and the following disclaimer in the documentation and/or other materials
## provided with the distribution.
##
## THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS "AS IS" AND ANY EXPRESS OR IMPLIED
## WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND
## FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR
## CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
## CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
## SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON
## ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
## NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF
## ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
##

EXE		= MacGPusher

SRCS		= MMGAPNSConnection.cpp \
		MMGSSLConnection.cpp \
		MMGDevice.cpp \
		MMGTools.cpp \
		MMGPayload.cpp \
		main.cpp

OBJS		= $(SRCS:.cpp=.o)
DEPS		= $(SRCS:.cpp=.d)

CXXFLAGS	+= -W -Wall -Wextra -Wno-unknown-pragma -I. -std=c++11
LDFLAGS		= -lssl -lcrypto
DEPSFLAGS	= -MMD

%.o:		%.cpp
		$(CXX) $(CXXFLAGS) $(DEPSFLAGS) -c -o $@ $<

all:		$(EXE)

$(EXE):		$(OBJS)
		$(CXX) $^ -o $@ $(LDFLAGS)


clean:
		$(RM) -f $(OBJS) $(DEPS)

distclean:	clean
		$(RM) -f $(EXE)

.PHONY:		all clean distclean

-include	$(DEPS)
