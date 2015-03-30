
#include "ShowObj.h"


using namespace std;

#define MAX(a, b, c) (a > b? (a > c? a : c):(b > c ? b : c));

#define MIN(a, b, c) (a > b? (b > c? c : b): (a < c? a : c));




ShowObj::ShowObj():polyCounts(0){
	
}
ShowObj::ShowObj(int width, int height):polyCounts(0){
	
	this->width = width;
	this->height = height;


}

void ShowObj::InitStruct(Scene s){
	Object* tmpObj = s.objects;
	
	while(tmpObj != NULL){
	
		vector<Facet> facets = tmpObj->solid->facets;
		int szOfFacet = facets.size();
		Transform* curTrans = tmpObj->transform;
		for(int i = 0; i < szOfFacet; i++){
			Facet faceAfterTrans = facets[i].doTransform(*curTrans);

			Tuple3d v1 = faceAfterTrans.point[1] - faceAfterTrans.point[0];
			Tuple3d v2 = faceAfterTrans.point[2] - faceAfterTrans.point[1];

			Tuple3d normal = v1.cross(v2);

			//������α����Ϣ��
			//�����ƽ���A��B��C��D��ֵ��
			polygons[polyCounts].A = normal.m_data[0];
			polygons[polyCounts].B = normal.m_data[1];
			polygons[polyCounts].C = normal.m_data[2];
			polygons[polyCounts].D = faceAfterTrans.point[1] * normal;

			polygons[polyCounts].id = polyCounts;

			

			double maxY = MAX(faceAfterTrans.point[0].m_data[1], faceAfterTrans.point[1].m_data[1],faceAfterTrans.point[2].m_data[1]);
			double minY = MIN(faceAfterTrans.point[0].m_data[1], faceAfterTrans.point[1].m_data[1],faceAfterTrans.point[2].m_data[1]);
			
			polygons[polyCounts].yCount = maxY - minY;

			polygons[polyCounts].next = NULL;
			//polygons[polyCounts].edge = NULL;

			//�������߱��С�
			int intMaxY = (int)maxY; 

			//�����Ժ�Ҫ�����жϣ����intMaxY̫�����ǲ�Ӧ����ӵġ���֮�����⡣



			if(polyLine[intMaxY].last == NULL){
				polyLine[intMaxY].first = &polygons[polyCounts];
				polyLine[intMaxY].last = polyLine[intMaxY].first;
			}else{
				polyLine[intMaxY].last->next = &polygons[polyCounts];
				polyLine[intMaxY].last = &polygons[polyCounts];
			}

			//�����ߵĳ�ʼ��,�����߱�

			Edge *e = new Edge[3];
			
			for(int k = 0; k < 3; k++){
				e[k].dx = (faceAfterTrans.point[k % 3].m_data[0] - faceAfterTrans.point[(k + 1) % 3].m_data[0]) /
						  (faceAfterTrans.point[k % 3].m_data[1] - faceAfterTrans.point[(k + 1) % 3].m_data[1]);//�õ���x��ֵ����y��ֵ��
				e[k].PolyId = polyCounts;
				e[k].next = NULL;


				if(faceAfterTrans.point[k % 3].m_data[1] > faceAfterTrans.point[(k + 1) % 3].m_data[1]){
					e[k].x = faceAfterTrans.point[k % 3].m_data[0];
				
					e[k].yCount = faceAfterTrans.point[k % 3].m_data[1] - faceAfterTrans.point[(k + 1) % 3].m_data[1];
					
					int iMaxY = (int)faceAfterTrans.point[k % 3].m_data[1];
					
					e[k].ymax = iMaxY;

					polygons[polyCounts].edges.push_back(&e[k]);
				
					
				}else{
					e[k].x = faceAfterTrans.point[k % 3].m_data[1];
				
					e[k].yCount = faceAfterTrans.point[(k + 1) % 3].m_data[1] - faceAfterTrans.point[k % 3].m_data[1];
					
					int iMaxY = (int)faceAfterTrans.point[(k + 1) % 3].m_data[1];
					
					e[k].ymax = iMaxY;

					polygons[polyCounts].edges.push_back(&e[k]);
					
				}

			}
			polyCounts++;

		}

		tmpObj = tmpObj->next;
	}
}

//����Ϊֹ������������������ȷ�ġ�
Buffer<double> ShowObj::CreateZBuffer(){
	ActivePoly *apt = NULL;
	ActiveEdge *aet = NULL;

	


	/*
	Edge *tmpEdge = edgeLine[height - 1].first;
	while(tmpEdge != NULL){
		
		ActiveEdge *ep = new ActiveEdge;
		
		ep->xl = tmpEdge->x;
		ep->dxl = tmpEdge->dx;
		ep->dyl = tmpEdge->yCount;

		//ep->xr = tmpEdge->

		//tmpEdge = tmpEdge->next;
		if(aet == NULL){
			aet = ep;
		}else{
			ep->next = aet;
			aet = ep;
		}
	}
	*/
	

	Buffer<double> buf(width, height, 64345654);


	for(int y = height - 1; y >= 0; y--){


		//����Ƿ����¼���Ķ���Ρ�
		if(polyLine[y].first != NULL){
				Polygon* tmpPoly = polyLine[height - 1].first;
				while(tmpPoly != NULL){
					ActivePoly *ap = new ActivePoly;
					ap->A = tmpPoly->A;
					ap->B = tmpPoly->B;
					ap->C = tmpPoly->C;
					ap->D = tmpPoly->D;

					ap->polyId = tmpPoly->id;
					ap->yCount = tmpPoly->yCount;

					for(int i = 0; i < tmpPoly->edges.size(); i++){

						if(ap->edgeLine[tmpPoly->edges[i]->ymax] == NULL){
							ap->edgeLine[tmpPoly->edges[i]->ymax] = tmpPoly->edges[i];
						} else{
							tmpPoly->edges[i]->next = ap->edgeLine[tmpPoly->edges[i]->ymax];
							ap->edgeLine[tmpPoly->edges[i]->ymax] = tmpPoly->edges[i];
						}

					}

					if(apt == NULL){
						apt = ap;
					}else{
						ap->next = apt;
						apt = ap;
					}

					//�����µĻ�߶Ա�
					ActiveEdge* ae = new ActiveEdge;
					//����������µı߶Կ���Ҫ��ӡ�
					if(ap->edgeLine[y] != NULL){
						//���ñȽ�ɵ��ѭ�������ķ�ʽ��
						Edge* tmpE1 = ap->edgeLine[y];
						while(tmpE1 != NULL){
							Edge* tmpE2 = tmpE1;
							while(tmpE2){
								if(tmpE1->x == tmpE2->x){
									if(tmpE1->dx > tmpE2->dx){
										Edge* swapTmp = tmpE1;
										tmpE1 = tmpE2;
										tmpE2 = tmpE1;
									}

									ae->dxl = tmpE1->dx;
									ae->dxr = tmpE2->dx;
									ae->dyl = tmpE1->yCount;
									ae->dyr = tmpE2->yCount;
									ae->xl = tmpE1->x;
									ae->xr = tmpE2->x;
									ae->polyId = ap->polyId;
									if(ap->C == 0){
										cout << "error ap->C equal to 0!!" << endl;
										system("pause");
									}else{
										ae->dzx = -ap->A / ap->C;
										ae->dzy = ap->B / ap->C;
										ae->zl = (ap->A * tmpE1->x + ap->B * y + ap->D) / ap->C;
									}
									
									ae->next = aet;
									aet = ae;
									ae = new ActiveEdge;
											
								}
							}
						}
					}
					delete ae;



					Polygon* dp = tmpPoly;
					
					tmpPoly = tmpPoly->next;
					
					delete dp;//Ū���ɾ����,��ʵ���Բ���Ū�������������Ļ�֮ǰ�ж���Ҫ�Ķ��ѡ�
					
				}
				

				
		}


		





		//�������α��Ƿ��ж�����������ж�Ӧ���޸ģ�������Ƿ���ڱ߶Խ����������
		if(apt != NULL){
			ActivePoly* tmpApt = apt;
			ActivePoly* prePoint = NULL;
			while(tmpApt){
				tmpApt->yCount -- ;//������������Ƿ�ɨ������ˡ�
				if(tmpApt->yCount == 0){//ʹ�õ���0�ж���
					if(prePoint == NULL){
						apt = tmpApt->next;
						delete tmpApt;
						tmpApt = apt;

					}else{
						prePoint->next = tmpApt->next;
						delete tmpApt;
						tmpApt = prePoint->next;
					}
				}else{
					//����ֻ����
					prePoint = tmpApt;
					tmpApt = tmpApt->next;
				}
				
			}
		}else{
			
		}

		//����߱��Ƿ��ж����������Ӧ���޸ģ�������Ƿ���ڽ����������
		if(aet != NULL){
			ActiveEdge* tmpAet = aet;
			ActiveEdge* preAEP = NULL;
			while(tmpAet){
				tmpAet->dyl--;
				tmpAet->dyr--;
				tmpAet->xl += tmpAet->dxl;
				tmpAet->xr += tmpAet->dxr;
				tmpAet->zl = tmpAet->zl + tmpAet->dzx * tmpAet->dxl + tmpAet->dzy;


				if(tmpAet->dyl == 0 || tmpAet->dyr == 0){//ʹ�õ���0�ж���
					//Ū���������ȱ��
					Edge *tmpEdge = edgeLine[y].first;
					Edge *preEP = NULL;
					while(tmpEdge != NULL){
						//�ҵ�һ���Ļ�
						if(tmpEdge->PolyId == tmpAet->polyId){
							if(tmpAet->dyl == 0){
								tmpAet->dyl = tmpEdge->yCount;
								tmpAet->dxl = tmpEdge->dx;
								tmpAet->xl = tmpEdge->x;
								
							}else if(tmpAet->dyr == 0){
								if(tmpAet->dxl < tmpEdge->x){
									tmpAet->dxr = tmpEdge->dx;
									tmpAet->dyr = tmpEdge->yCount;
									tmpAet->xr = tmpEdge->x;
								}else{
									tmpAet->dxr = tmpAet->dxl;
									tmpAet->dyr = tmpAet->dyl;
									tmpAet->xr = tmpAet->xl;

									tmpAet->dxl = tmpEdge->dx;
									tmpAet->dyl = tmpEdge->yCount;
									tmpAet->xl = tmpEdge->x;
								}

							}
							if(preEP == NULL){
								edgeLine[y].first = tmpEdge->next;
								delete tmpEdge;
								tmpEdge = edgeLine[y].first;
							}else{
								preEP->next = tmpEdge->next;
								delete tmpEdge;
								tmpEdge = preEP->next;
							}
						
						}
					}

					if(tmpAet->dyl == 0 || tmpAet->dyr == 0){
						//Ū�����������ʶ�ɾ����
						if(preAEP == NULL){
							aet = tmpAet->next;
							delete tmpAet;
							tmpAet = aet;
						}else{
							preAEP->next = tmpAet->next;
							delete tmpAet;
							tmpAet = preAEP->next;
						}
					}else{
						tmpAet = tmpAet->next;
					}

					
				}
			}
		}

		
		//�������Ƿ����


		for(int x = 0; x < width; x++){
			ActiveEdge* tmpAE = aet;

			while(tmpAE){
				double zx = tmpAE->xl;
				for(int i = tmpAE->xl; i <= tmpAE->xr; i++){
					if(buf.at(y, i) < zx){
						buf.at(y, i) = zx;
					}
					zx += tmpAE->dzx;
				}

				tmpAE = tmpAE->next;
			}

		}

	}
	return buf;
}




