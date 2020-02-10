#ifndef GOL_ACTION_KEY_BINDING
#define GOL_ACTION_KEY_BINDING


#include <vector>

class GoLModel;
class GoLController;


class GoLActionKeyBinding
{
public:
	using key_t = int;
	using action_t = void(*)(GoLModel & model, GoLController & controller);

	GoLActionKeyBinding(); // for char
	GoLActionKeyBinding(key_t bindFromKey, key_t bindToKey);

	void setAction(key_t key, action_t action);
	void setDefaultAction(action_t action);
	void setDefaultAction(key_t key);

	void doActionFromKey(key_t key, GoLModel & model, GoLController & controller) const;
	void doDefaultAction(GoLModel & model, GoLController & controller) const;

private:
	key_t mOffsetKey;
	std::vector<action_t> mBinding;
	action_t mDefaultAction = nullptr;
};


#endif // GOL_ACTION_KEY_BINDING
