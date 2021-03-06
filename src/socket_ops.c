/*
 * Copyright (C) 2014 Joel Schlosser All Rights Reserved.
 *
 * This file is part of smudge.
 *
 * smudge is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * smudge is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with smudge.  If not, see <http://www.gnu.org/licenses/>.
 *
 */

#include "socket_ops.h"

const socket_ops REAL_SOCKET_OPS = {
    .freeaddrinfo = freeaddrinfo,
    .getaddrinfo = getaddrinfo,
    .socket = socket,
    .connect = connect,
    .select = select,
    .send = send,
    .recv = recv,
    .ioctl = ioctl
};
