#include <vtkRenderWindowInteractor.h>
#include <vtkRenderWindow.h>
#include <vtkRenderer.h>
#include <vtkCamera.h>
#include <vtk3DSImporter.h>
#include <vtkSmartPointer.h>
#include <vtkRenderLargeImage.h>
#include <vtkTIFFWriter.h>
#include <vtkBMPReader.h>
#include <vtkPointData.h>
#include <vtkAutoInit.h>

#include <vector>
using namespace std;

#include <windows.h>

VTK_MODULE_INIT(vtkRenderingOpenGL2);
VTK_MODULE_INIT(vtkInteractionStyle);

string file_path = "装配散件模型.3DS";
//string file_path = "汽缸盖.3DS";

int main()
{
	vtkSmartPointer<vtkRenderWindowInteractor> iren = 
		vtkSmartPointer<vtkRenderWindowInteractor>::New();
	vtkSmartPointer<vtkRenderWindow> renWin = vtkSmartPointer<vtkRenderWindow>::New();
	vtkSmartPointer<vtkRenderer> renderer = vtkSmartPointer<vtkRenderer>::New();

	iren->SetRenderWindow(renWin);
	renWin->AddRenderer(renderer);

	renderer->SetBackground(0.1, 0.2, 0.4);
	renWin->SetSize(600, 600);

	vtkSmartPointer<vtk3DSImporter> importer = vtkSmartPointer<vtk3DSImporter>::New();
	importer->SetFileName(file_path.c_str());
	importer->ComputeNormalsOn();
	importer->Read();

	renderer->GetActiveCamera()->SetPosition(0, 500, 0);
	renderer->GetActiveCamera()->SetFocalPoint(0, 0, 0);
	renderer->GetActiveCamera()->SetViewUp(0, 0, 1);

	// 从3ds图像中依次读取物体 
	int numOfActors = importer->GetRenderer()->GetActors()->GetNumberOfItems();
	for (int i = 0; i < numOfActors; i++)
	{
		vtkActor *actor = (vtkActor *)importer->GetRenderer()->GetActors()->GetItemAsObject(i);
		//actor->SetScale(0.5,1,1);
		renderer->AddActor(actor);
	}

	renWin->Render();
	iren->Start();

	return 0;
}