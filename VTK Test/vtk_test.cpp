#include <vtkRenderWindowInteractor.h>
#include <vtkRenderWindow.h>
#include <vtkRenderer.h>
#include <vtkCamera.h>
#include <vtk3DSImporter.h>
#include <vtkOBJImporter.h>
#include <vtkSmartPointer.h>
#include <vtkRenderLargeImage.h>
#include <vtkAutoInit.h>

#include <string>
#include <windows.h>

VTK_MODULE_INIT(vtkRenderingOpenGL2);
VTK_MODULE_INIT(vtkInteractionStyle);

std::string file_path = "װ��ɢ��ģ��";
//std::string file_path = "���׸�";

int main()
{
	vtkSmartPointer<vtkRenderWindowInteractor> iren = 
		vtkSmartPointer<vtkRenderWindowInteractor>::New();	// �������ڽ�����
	vtkSmartPointer<vtkRenderWindow> renWin = 
		vtkSmartPointer<vtkRenderWindow>::New();			// ������Ⱦ����
	vtkSmartPointer<vtkRenderer> renderer = 
		vtkSmartPointer<vtkRenderer>::New();				// ������Ⱦ��

	iren->SetRenderWindow(renWin);		// ���ý��������ƵĴ���ΪrenWin
	renWin->AddRenderer(renderer);		// ����Ⱦ��renderer��ӵ�����renWin����Ⱦ���б���

	renderer->SetBackground(0.1, 0.2, 0.4);			// ���ñ���ɫ
	renWin->SetSize(600, 600);			// ���ô��ڵ�Ĭ�ϴ�С

	vtkSmartPointer<vtkOBJImporter> importer = 
		vtkSmartPointer<vtkOBJImporter>::New();		// ����3DS����������
	importer->SetFileName(std::string(file_path + ".obj").c_str());		// ָ��Ҫ��ȡ��3DS�ļ����ļ�����·��
	importer->SetFileNameMTL(std::string(file_path + ".mtl").c_str());
	//importer->ComputeNormalsOn();		// ��������������
	importer->Read();					// ����3DSģ��

	renderer->GetActiveCamera()->SetPosition(100, 200, 0);	// ���������λ��(��������ϵ��)
	renderer->GetActiveCamera()->SetFocalPoint(100, 0, 50);	// ��������Ľ���(��������ϵ��)
	renderer->GetActiveCamera()->SetViewUp(0, 0, 1);		// ��������Ĺ۲���ͼ

	// ��ȡ���ص�3DSģ�����������ĸ���
	int numOfActors = importer->GetRenderer()->GetActors()->GetNumberOfItems();

	// ��3dsͼ�������ζ�ȡ����
	for (int i = 0; i < numOfActors; i++)
	{
		vtkActor *actor = (vtkActor *)importer->GetRenderer()->GetActors()->GetItemAsObject(i);
		renderer->AddActor(actor);		// �������ȡ��������ӵ���Ⱦ����
	}

	renWin->Render();			// ����Ⱦ����renWin�е�������Ⱦ����ʼ��Ⱦ
	iren->Start();				// ��ʼ�¼�ѭ��

	return 0;
}