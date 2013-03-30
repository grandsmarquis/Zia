#ifndef __BODY_H__
# define __BODY_H__


class Body
{
	char		*_body;
	int			_length;
public:
	Body(char *body, int lenght);
	~Body();
	char *					getBody();
	int						getBodyLength() const;
	void					setBody(char *body, int lenght);
};

#endif // !_BODY_H_
