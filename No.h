using namespace std;

class Node
{
public:
	Node() 
	{
		Clean();
	}

	~Node() 
	{
		Clean();
	}

	void Clean()
	{
		children[0] = nullptr;
		children[1] = nullptr;
		children[2] = nullptr;
		children[3] = nullptr;
		children[4] = nullptr;

		values[0] = 0;
		values[1] = 0;
		values[2] = 0;
		values[3] = 0;

		valuesCount = 0;
	}

	bool IsEmpty()
	{
		return valuesCount <= 0;
	}

	bool IsFull()
	{
		return valuesCount >= 4;
	}

	int AddValue(int iValor)
	{
		int iReturnPos = -1;

		if(valuesCount >= 4)
			return iReturnPos;

		if(!valuesCount)
		{
			values[0] = iValor;
			iReturnPos = 0;
		}

		values[valuesCount] = iValor;
		iReturnPos = valuesCount;
		for(int i = valuesCount - 1; i >= 0; --i)
		{
			if(iValor < values[i])
			{
				int temp = values[i];
				values[i] = iValor;
				values[iReturnPos] = temp;
				Node* temp2 = children[i];
				Node* temp3 = children[i+1];
				children[i] = nullptr;
				children[i+1] = nullptr;
				children[iReturnPos] = temp2;
				children[iReturnPos+1] = temp3;
				iReturnPos = i;
			}
		}

		++valuesCount;
		return iReturnPos;
	}

	void RemoveValue(int idx)
	{
		if(idx >= 4)
			return;

		bool bReallocate = false;
		for(int i = 0; i < valuesCount; ++i)
		{
			if (bReallocate)
			{
				values[i-1] = values[i];
				children[i-1] = children[i];
				children[i] = children[i+1];
			}
			else if (i == idx)
			{
				bReallocate = true;
			}
		}

		--valuesCount;
	}

	int GetMaxValueIdx()
	{
		return (valuesCount - 1);
	}

	int GetValuesCount()
	{
		return valuesCount;
	}

	bool HasChildren()
	{
		return (children[0] || children[1] || children[2] || children[3] || children[4]);
	}

	int GetValue(int idx)
	{
		return values[idx];
	}

	void SetChild(int idx, Node* filho)
	{
		children[idx] = filho;
	}

	Node* GetChild(int idx)
	{
		if(idx > 4)
			return nullptr;

		return children[idx];
	}

private:
	int values[4];
	Node* children[5];
	int valuesCount;
};

struct PARTITIONED{
	int infos[5];

	PARTITIONED(){
		infos[0] = 0;
		infos[1] = 0;
		infos[2] = 0;
		infos[3] = 0;
		infos[4] = 0;
	}
};

struct EXACT_NODE
{
	Node* node;
	int iPosition;

	EXACT_NODE()
	{
		node = nullptr;
		iPosition = -1;
	}

	bool EXACT_NODE::IsValid()
	{
		return (node != nullptr && iPosition >= 0);
	}

	Node* GetLeftChild()
	{
		if(!node)
			return nullptr;

		return node->GetChild(iPosition);
	}

	Node* GetRightChild()
	{
		if(!node || iPosition >= 4)
			return nullptr;

		return node->GetChild(iPosition + 1);
	}

	int GetValue()
	{
		if(!node)
			return 0;

		return node->GetValue(iPosition);
	}
};

class BTree
{
public:
	BTree()
	{
		m_pRoot = nullptr;
	}

	~BTree() {}

	void Insert(int info)
	{
		EXACT_NODE no;
		InsertRec(info, no);
	}

	EXACT_NODE GetNodeInfo(int info)
	{
		return GetNodeInfo(m_pRoot, info);
	}

	bool Exists(int info)
	{
		return ExistsRec(m_pRoot, info);
	}

	void Remove(int info)
	{
		EXACT_NODE exactNode = GetNodeInfo(info);

		if(!exactNode.GetLeftChild() && !exactNode.GetRightChild())
			exactNode.node->RemoveValue(exactNode.iPosition);
		else
		{

		}
	}

private:
	EXACT_NODE InsertRec(int info, EXACT_NODE nodoPos)
	{
		EXACT_NODE exactNode;
		Node* pPrevious = nullptr;
		Node* pTemp;

		if(nodoPos.IsValid())
		{
			if(nodoPos.GetLeftChild() == nullptr)
			{
				Node* newChild = new Node;
				exactNode.iPosition = newChild->AddValue(info);
				exactNode.node = newChild;
				nodoPos.node->SetChild(nodoPos.iPosition, newChild);
				return exactNode;
			}

			if(nodoPos.GetLeftChild()->IsEmpty())
			{
				Node* newChild = new Node;
				exactNode.iPosition = newChild->AddValue(info);
				exactNode.node = newChild;
				nodoPos.node->SetChild(nodoPos.iPosition, newChild);
				return exactNode;
			}

			pTemp = nodoPos.GetLeftChild();
		}
		else
		{
			if(nodoPos.node)
			{
				pTemp = nodoPos.node;

				if(pTemp->IsFull())
				{
					PARTITIONED part = Partition(info, pTemp);
					pTemp->Clean();
					EXACT_NODE exactNode;
					exactNode.node = pPrevious;
					exactNode = InsertRec(part.infos[0], exactNode);
					InsertRec(part.infos[1], exactNode);
					InsertRec(part.infos[2], exactNode);
					exactNode.iPosition += 1;
					InsertRec(part.infos[3], exactNode);
					InsertRec(part.infos[4], exactNode);
				}
				else
				{
					exactNode.iPosition = pTemp->AddValue(info);
					exactNode.node = pTemp;
					return exactNode;
				}
			}
			else
			{
				if(m_pRoot == nullptr)
				{
					m_pRoot = new Node;
					exactNode.iPosition = m_pRoot->AddValue(info);
					exactNode.node = m_pRoot;
					return exactNode;
				}

				if(m_pRoot->IsEmpty())
				{
					m_pRoot = new Node;
					exactNode.iPosition = m_pRoot->AddValue(info);
					exactNode.node = m_pRoot;
					return exactNode;
				}

				pTemp = m_pRoot;
			}
		}

		while(pTemp != nullptr)
		{
			if(pTemp->HasChildren())
			{
				for(int i = 0; i < pTemp->GetValuesCount(); ++i)
				{
					if(info < pTemp->GetValue(i))
					{
						pPrevious = pTemp;
						pTemp = pTemp->GetChild(i);
						break;
					}
					else 
						if(i == pTemp->GetValuesCount() - 1)
						{
							pPrevious = pTemp;
							pTemp = pTemp->GetChild(i+1);
							break;
						}
				}

				if(!pTemp)
				{
					pTemp = new Node();
					exactNode.iPosition = pTemp->AddValue(info);
					exactNode.node = pTemp;
					return exactNode;
				}

				if(pTemp->IsEmpty())
				{
					pTemp = new Node();
					exactNode.iPosition = pTemp->AddValue(info);
					exactNode.node = pTemp;
					return exactNode;
				}
			}
			else 
			{
				if(pTemp->IsFull())
				{
					PARTITIONED part = Partition(info, pTemp);
					pTemp->Clean();
					EXACT_NODE exactNode;
					exactNode.node = pPrevious;
					exactNode = InsertRec(part.infos[0], exactNode);
					InsertRec(part.infos[1], exactNode);
					InsertRec(part.infos[2], exactNode);
					exactNode.iPosition += 1;
					InsertRec(part.infos[3], exactNode);
					InsertRec(part.infos[4], exactNode);
				}
				else
				{
					exactNode.iPosition = pTemp->AddValue(info);
					exactNode.node = pTemp;
					return exactNode;
				}
			}
		}

		return exactNode;
	}

	PARTITIONED Partition(int info, Node* no)
	{
		PARTITIONED part;

		if(!no)
			return part;

		int temp[5];
		bool infoAlreadyAdded = false;

		for(int i = 0, j = 0; i < 5 && j < 4; ++i, ++j)
		{
			if(!infoAlreadyAdded)
			{
				if(info < no->GetValue(j))
				{
					temp[i] = info;
					--j;
					infoAlreadyAdded = true;
					continue;
				}
			}

			if(!infoAlreadyAdded)
				temp[4] = info;

			temp[i] = no->GetValue(j);
		}

		part.infos[0] = temp[2];
		part.infos[1] = temp[0];
		part.infos[2] = temp[1];
		part.infos[3] = temp[3];
		part.infos[4] = temp[4];

		return part;
	}

	bool ExistsRec(Node* no, int info)
	{
		while(no != nullptr)
		{
			for(int i = 0; i < no->GetValuesCount(); ++i)
			{
				if(info == no->GetValue(i))
					return true;

				if(info < no->GetValue(i))
				{
					no = no->GetChild(i);
					break;
				}
				else
					if(i == no->GetValuesCount() - 1)
					{
						no = no->GetChild(i+1);
						break;
					}
			}
		}

		return false;
	}

	EXACT_NODE GetNodeInfo(Node* node, int info)
	{
		EXACT_NODE exactNode;

		while(node != nullptr)
		{
			for(int i = 0; i < node->GetValuesCount(); ++i)
			{
				if(info == node->GetValue(i))
				{
					exactNode.iPosition = i;
					exactNode.node = node;
					return exactNode;
				}

				if(info < node->GetValue(i))
				{
					node = node->GetChild(i);
					break;
				}
				else if (i == node->GetValuesCount() - 1)
				{
					node = node->GetChild(i+1);
					break;
				}
			}
		}

		return exactNode;
	}
	
	EXACT_NODE GetMax(Node* no)
	{
		while(no)
		{
			int idx = no->GetMaxValueIdx();
			if(no->GetChild(idx + 1))
				no = no->GetChild(idx + 1);
		}
	}

	Node* m_pRoot;
};

