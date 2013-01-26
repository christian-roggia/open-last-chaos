/******************************************************************************************
  Copyright 2013 Christian Roggia

   Licensed under the Apache License, Version 2.0 (the "License");
   you may not use this file except in compliance with the License.
   You may obtain a copy of the License at

       http://www.apache.org/licenses/LICENSE-2.0

   Unless required by applicable law or agreed to in writing, software
   distributed under the License is distributed on an "AS IS" BASIS,
   WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
   See the License for the specific language governing permissions and
   limitations under the License.
******************************************************************************************/

#ifndef SERVERRUN_H
#define SERVERRUN_H

#include "Descriptor.h"
#include "Server.h"
#include "Utils.h"

#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/select.h>

int InitFDSET(int, CDescriptor *, fd_set *, fd_set *, fd_set *);

#endif
