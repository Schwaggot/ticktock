/*
    TickTock is an open-source Time Series Database, maintained by
    Yongtao You (yongtao.you@gmail.com) and Yi Lin (ylin30@gmail.com).

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <https://www.gnu.org/licenses/>.
 */

#include <cstring>
#include "memmgr.h"
#include "strbuf.h"
#include "utils.h"


namespace tt
{


StringBuffer::StringBuffer() :
    m_cursor(0)
{
    m_buffs.push_back(MemoryManager::alloc_network_buffer());
}

StringBuffer::~StringBuffer()
{
    for (char *buff: m_buffs)
    {
        MemoryManager::free_network_buffer(buff);
    }
}

char *
StringBuffer::strdup(const char *str)
{
    size_t buff_size = MemoryManager::get_network_buffer_size() - 2;

    ASSERT(str != nullptr);
    ASSERT(std::strlen(str) < buff_size);

    size_t len = std::strlen(str);

    if ((m_cursor + len) >= buff_size)
    {
        m_cursor = 0;
        m_buffs.push_back(MemoryManager::alloc_network_buffer());
    }

    char *buff = m_buffs.back() + m_cursor;
    std::strncpy(buff, str, len+1);
    m_cursor += len + 1;

    return buff;
}


}
