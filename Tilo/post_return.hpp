// Do something after a return statement has been reached

#ifndef TILO_POST_RETURN_HPP
#define TILO_POST_RETURN_HPP

#define POST_RETURN(_stmt) \
	struct _PostReturn { \
		~_PostReturn() {\
			_stmt \
		} \
	} _postReturn


#endif