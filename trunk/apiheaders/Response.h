#ifndef __RESPONSE_H__
# define __RESPONSE_H__

#include "ResponseHeader.h"
#include "Body.h"

class Response
{
	char	*_buffer;
	int		_bufferLength;
	ResponseHeader		_header;
	Body				_body;
public:
	Response(char *buffer, int bufferLength);
	~Response();
	void				assemble();
	Body &				getBody();
	char				*getBuffer();
	ResponseHeader &	getHeader();
	int					getLength() const;
};

#endif // !_RESPONSE_H_
