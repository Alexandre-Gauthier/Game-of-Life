#ifndef ECA_ACTION_KEY_BINDING
#define ECA_ACTION_KEY_BINDING


#include <vector>

class EcaModel;
class EcaController;


class EcaActionKeyBinding
{
public:
	using key_t = int;
	using action_t = void(*)(EcaModel & model, EcaController & controller);

	EcaActionKeyBinding(); // for char
	EcaActionKeyBinding(key_t bindFromKey, key_t bindToKey);

	void setAction(key_t key, action_t action);
	void setDefaultAction(action_t action);
	void setDefaultAction(key_t key);

	void doActionFromKey(key_t key, EcaModel & model, EcaController & controller) const;
	void doDefaultAction(EcaModel & model, EcaController & controller) const;

private:
	key_t mOffsetKey;
	std::vector<action_t> mBinding;
	action_t mDefaultAction = nullptr;
};


#endif // ECA_ACTION_KEY_BINDING
