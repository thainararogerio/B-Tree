using namespace std;

class No
{
public:
	No() 
	{
		Limpa();
	}

	~No() 
	{
		Limpa();
	}

	void Limpa()
	{
		filhos[0] = nullptr;
		filhos[1] = nullptr;
		filhos[2] = nullptr;
		filhos[3] = nullptr;
		filhos[4] = nullptr;

		valores[0] = 0;
		valores[1] = 0;
		valores[2] = 0;
		valores[3] = 0;

		qtdValores = 0;
	}

	bool EstaVazio()
	{
		return qtdValores <= 0;
	}

	bool EstaCheio()
	{
		return qtdValores >= 4;
	}

	int AdicionaValor(int iValor)
	{
		int iPosicaoRetornada = -1;

		if(qtdValores >= 4)
			return iPosicaoRetornada;

		if(!qtdValores)
		{
			valores[0] = iValor;
			iPosicaoRetornada = 0;
		}

		valores[qtdValores] = iValor;
		iPosicaoRetornada = qtdValores;
		for(int i = qtdValores - 1; i >= 0; --i)
		{
			if(iValor < valores[i])
			{
				int temp = valores[i];
				valores[i] = iValor;
				valores[iPosicaoRetornada] = temp;
				No* temp2 = filhos[i];
				No* temp3 = filhos[i+1];
				filhos[i] = nullptr;
				filhos[i+1] = nullptr;
				filhos[iPosicaoRetornada] = temp2;
				filhos[iPosicaoRetornada+1] = temp3;
				iPosicaoRetornada = i;
			}
		}

		++qtdValores;
		return iPosicaoRetornada;
	}

	void RemoveValor(int idx)
	{
		if(idx >= 4)
			return;

		bool bRealocar = false;
		for(int i = 0; i < qtdValores; ++i)
		{
			if(bRealocar)
			{
				valores[i-1] = valores[i];
				filhos[i-1] = filhos[i];
				filhos[i] = filhos[i+1];
			}
			else
				if(i == idx)
					bRealocar = true;
		}

		--qtdValores;
	}

	int GetIdxMaiorValor()
	{
		return (qtdValores - 1);
	}

	int GetQuantidadeValores()
	{
		return qtdValores;
	}

	bool TemFilhos()
	{
		return (filhos[0] || filhos[1] || filhos[2] || filhos[3] || filhos[4]);
	}

	int GetValor(int idx)
	{
		return valores[idx];
	}

	void SetFilho(int idx, No* filho)
	{
		filhos[idx] = filho;
	}

	No* GetFilho(int idx)
	{
		if(idx > 4)
			return nullptr;

		return filhos[idx];
	}

private:
	int valores[4];
	No* filhos[5];
	int qtdValores;
};

struct PARTICIONADO{
	int infos[5];

	PARTICIONADO(){
		infos[0] = 0;
		infos[1] = 0;
		infos[2] = 0;
		infos[3] = 0;
		infos[4] = 0;
	}
};

struct NODO_EXATO
{
	No* nodo;
	int iPosicao;

	NODO_EXATO()
	{
		nodo = nullptr;
		iPosicao = -1;
	}

	bool NODO_EXATO::EhValido()
	{
		return (nodo != nullptr && iPosicao >= 0);
	}

	No* GetFilhoEsquerda()
	{
		if(!nodo)
			return nullptr;

		return nodo->GetFilho(iPosicao);
	}

	No* GetFilhoDireita()
	{
		if(!nodo || iPosicao >= 4)
			return nullptr;

		return nodo->GetFilho(iPosicao + 1);
	}

	int GetValor()
	{
		if(!nodo)
			return 0;

		return nodo->GetValor(iPosicao);
	}
};

class ArvoreB
{
public:
	ArvoreB()
	{
		m_pRaiz = nullptr;
	}

	~ArvoreB() {}

	void Insere(int info)
	{
		NODO_EXATO no;
		InsereRec(info, no);
	}

	NODO_EXATO GetNoInfo(int info)
	{
		return GetNoInfo(m_pRaiz, info);
	}

	bool Existe(int info)
	{
		return ExisteRec(m_pRaiz, info);
	}

	void Remove(int info)
	{
		NODO_EXATO nodoExato = GetNoInfo(info);

		if(!nodoExato.GetFilhoEsquerda() && !nodoExato.GetFilhoDireita())
			nodoExato.nodo->RemoveValor(nodoExato.iPosicao);
		else
		{

		}
	}

private:
	NODO_EXATO InsereRec(int info, NODO_EXATO nodoPos)
	{
		NODO_EXATO nodoRetorno;
		No* pAnterior = nullptr;
		No* pTemp;

		if(nodoPos.EhValido())
		{
			if(nodoPos.GetFilhoEsquerda() == nullptr)
			{
				No* filhoNovo = new No;
				nodoRetorno.iPosicao = filhoNovo->AdicionaValor(info);
				nodoRetorno.nodo = filhoNovo;
				nodoPos.nodo->SetFilho(nodoPos.iPosicao, filhoNovo);
				return nodoRetorno;
			}

			if(nodoPos.GetFilhoEsquerda()->EstaVazio())
			{
				No* filhoNovo = new No;
				nodoRetorno.iPosicao = filhoNovo->AdicionaValor(info);
				nodoRetorno.nodo = filhoNovo;
				nodoPos.nodo->SetFilho(nodoPos.iPosicao, filhoNovo);
				return nodoRetorno;
			}

			pTemp = nodoPos.GetFilhoEsquerda();
		}
		else
		{
			if(nodoPos.nodo)
			{
				pTemp = nodoPos.nodo;

				if(pTemp->EstaCheio())
				{
					PARTICIONADO part = Particiona(info, pTemp);
					pTemp->Limpa();
					NODO_EXATO nodoExato;
					nodoExato.nodo = pAnterior;
					nodoExato = InsereRec(part.infos[0], nodoExato);
					InsereRec(part.infos[1], nodoExato);
					InsereRec(part.infos[2], nodoExato);
					nodoExato.iPosicao += 1;
					InsereRec(part.infos[3], nodoExato);
					InsereRec(part.infos[4], nodoExato);
				}
				else
				{
					nodoRetorno.iPosicao = pTemp->AdicionaValor(info);
					nodoRetorno.nodo = pTemp;
					return nodoRetorno;
				}
			}
			else
			{
				if(m_pRaiz == nullptr)
				{
					m_pRaiz = new No;
					nodoRetorno.iPosicao = m_pRaiz->AdicionaValor(info);
					nodoRetorno.nodo = m_pRaiz;
					return nodoRetorno;
				}

				if(m_pRaiz->EstaVazio())
				{
					m_pRaiz = new No;
					nodoRetorno.iPosicao = m_pRaiz->AdicionaValor(info);
					nodoRetorno.nodo = m_pRaiz;
					return nodoRetorno;
				}

				pTemp = m_pRaiz;
			}
		}

		while(pTemp != nullptr)
		{
			if(pTemp->TemFilhos())
			{
				for(int i = 0; i < pTemp->GetQuantidadeValores(); ++i)
				{
					if(info < pTemp->GetValor(i))
					{
						pAnterior = pTemp;
						pTemp = pTemp->GetFilho(i);
						break;
					}
					else 
						if(i == pTemp->GetQuantidadeValores() - 1)
						{
							pAnterior = pTemp;
							pTemp = pTemp->GetFilho(i+1);
							break;
						}
				}

				if(!pTemp)
				{
					pTemp = new No();
					nodoRetorno.iPosicao = pTemp->AdicionaValor(info);
					nodoRetorno.nodo = pTemp;
					return nodoRetorno;
				}

				if(pTemp->EstaVazio())
				{
					pTemp = new No();
					nodoRetorno.iPosicao = pTemp->AdicionaValor(info);
					nodoRetorno.nodo = pTemp;
					return nodoRetorno;
				}
			}
			else 
			{
				if(pTemp->EstaCheio())
				{
					PARTICIONADO part = Particiona(info, pTemp);
					pTemp->Limpa();
					NODO_EXATO nodoExato;
					nodoExato.nodo = pAnterior;
					nodoExato = InsereRec(part.infos[0], nodoExato);
					InsereRec(part.infos[1], nodoExato);
					InsereRec(part.infos[2], nodoExato);
					nodoExato.iPosicao += 1;
					InsereRec(part.infos[3], nodoExato);
					InsereRec(part.infos[4], nodoExato);
				}
				else
				{
					nodoRetorno.iPosicao = pTemp->AdicionaValor(info);
					nodoRetorno.nodo = pTemp;
					return nodoRetorno;
				}
			}
		}

		return nodoRetorno;
	}

	PARTICIONADO Particiona(int info, No* no)
	{
		PARTICIONADO part;

		if(!no)
			return part;

		int temp[5];
		bool jainseriuinfo = false;

		for(int i = 0, j = 0; i < 5 && j < 4; ++i, ++j)
		{
			if(!jainseriuinfo)
			{
				if(info < no->GetValor(j))
				{
					temp[i] = info;
					--j;
					jainseriuinfo = true;
					continue;
				}
			}

			if(!jainseriuinfo)
				temp[4] = info;

			temp[i] = no->GetValor(j);
		}

		part.infos[0] = temp[2];
		part.infos[1] = temp[0];
		part.infos[2] = temp[1];
		part.infos[3] = temp[3];
		part.infos[4] = temp[4];

		return part;
	}

	bool ExisteRec(No* no, int info)
	{
		while(no != nullptr)
		{
			for(int i = 0; i < no->GetQuantidadeValores(); ++i)
			{
				if(info == no->GetValor(i))
					return true;

				if(info < no->GetValor(i))
				{
					no = no->GetFilho(i);
					break;
				}
				else
					if(i == no->GetQuantidadeValores() - 1)
					{
						no = no->GetFilho(i+1);
						break;
					}
			}
		}

		return false;
	}

	NODO_EXATO GetNoInfo(No* no, int info)
	{
		NODO_EXATO retorno;

		while(no != nullptr)
		{
			for(int i = 0; i < no->GetQuantidadeValores(); ++i)
			{
				if(info == no->GetValor(i))
				{
					retorno.iPosicao = i;
					retorno.nodo = no;
					return retorno;
				}

				if(info < no->GetValor(i))
				{
					no = no->GetFilho(i);
					break;
				}
				else
					if(i == no->GetQuantidadeValores() - 1)
					{
						no = no->GetFilho(i+1);
						break;
					}
			}
		}

		return retorno;
	}
	
	NODO_EXATO GetMaior(No* no)
	{
		while(no)
		{
			int idx = no->GetIdxMaiorValor();
			if(no->GetFilho(idx + 1))
				no = no->GetFilho(idx + 1);
		}
	}

	No* m_pRaiz;
};

