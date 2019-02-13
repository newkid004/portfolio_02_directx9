#pragma once
#include "kGlobalDefine.h"
#include "pathfind_grape.h"

class aStar_path;
class aStar_node;

class aStar_grape : public pathfind_grape
{
public :
	typedef std::vector<aStar_node*> LIST;
	typedef std::unordered_map<int, std::vector<int>> CONNECTION;

public :
	struct info_distance
	{
		float F = 0.0f;
		float G = 0.0f;
		float H = 0.0f;
	};

protected :
	LIST _vNodeList;
	CONNECTION _mConnection;

	// test
	aStar_node* _currentNode = nullptr;
	aStar_node* _destNode = nullptr;

public :
	virtual void addNode(aStar_node* input);

	virtual bool deleteNode(aStar_node* input);
	virtual bool deleteNode(int index);

	virtual bool connectNode(aStar_node* n1, aStar_node* n2, bool reConnect = true);
	virtual bool connectNode(int index1, int index2);

	void pathfind(aStar_path** out_path, aStar_node* sour, aStar_node* dest);

public :
	void runGrape(const std::function<void(aStar_node* from, aStar_node* to)> & callback);

public :
	static float calDistance(aStar_node* n1, aStar_node* n2);
	static float calDistance(aStar_node* n1, D3DXVECTOR3 & pos);

public :
	aStar_node* operator[](int index) { return _vNodeList[index]; }

public :
	constexpr LIST & getNodeList(void) { return _vNodeList; }
	constexpr CONNECTION & getNodeConnection(void) { return _mConnection; }

	// test
	aStar_node* getCurrentNode(void) { return _currentNode; }
	aStar_node* getDestNode(void) { return _destNode; }

public:
	aStar_grape() {};
	~aStar_grape();
};