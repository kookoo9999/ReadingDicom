#include "stdafx.h"
#include "VolumeData.h"
#include "DVManager.h"
#include "MainFrm.h"
VolumeData::VolumeData()
{
	m_CurrentPresetMode = MIP;

	for( int i = 0; i < 3; i++ ) m_SliceIndex[i] = 0;
}


VolumeData::~VolumeData()
{
}
void VolumeData::ReadyForVolumeRendering()
{
	// Volume Mapper �غ�
	vtkSmartPointer<vtkSmartVolumeMapper> smartMapper = vtkSmartPointer<vtkSmartVolumeMapper>::New();
	smartMapper->SetInputData(m_ImageData);
	//double *fMinMax = m_ImageData->GetPointData()->GetScalars()->GetRange();
	// ���� �Լ�, �÷� �Լ� �غ�
	double scalarRange[2];
	m_ImageData->GetScalarRange(scalarRange);
	TRACE2("scalar[0] = %lf scalar[1] = %lf \n", scalarRange[0], scalarRange[1]);
	m_OpacityFunc = vtkSmartPointer<vtkPiecewiseFunction>::New();
	//m_OpacityFunc->AdjustRange( scalarRange );
	m_ColorFunc = vtkSmartPointer<vtkColorTransferFunction>::New();

	// Volume �Ӽ� �غ�
	vtkSmartPointer<vtkVolumeProperty> volumeProperty =
		vtkSmartPointer<vtkVolumeProperty>::New();

	volumeProperty->SetColor(0, m_ColorFunc);
	volumeProperty->ShadeOn();
	volumeProperty->SetInterpolationTypeToLinear();

	//0616 ����
	volumeProperty->SetDiffuse(0.7);
	volumeProperty->SetSpecular(0.3);
	volumeProperty->SetSpecularPower(30.0);
	volumeProperty->SetScalarOpacity(0, m_OpacityFunc);


	// Volume ȸ�� ��ȯ 
	double origin[3];
	m_ImageData->GetOrigin(origin);
	vtkSmartPointer<vtkTransform> userTransform =
		vtkSmartPointer<vtkTransform>::New();
	userTransform->Translate(origin);
	userTransform->Concatenate(GetOrientation());
	userTransform->Translate(-origin[0], -origin[1], -origin[2]);
	userTransform->Update();

	// Volume ������ ��ü ����
	m_VolumeRendering = vtkSmartPointer<vtkVolume>::New();
	m_VolumeRendering->SetMapper(smartMapper);
	m_VolumeRendering->SetProperty(volumeProperty);
	m_VolumeRendering->SetUserTransform(userTransform);

	//������ ��� �غ�
	SetCurrentPresetMode(MIP);
}
void VolumeData::SetCurrentPresetMode(int val)
{
	// Volume Rendering �غ� ����
	if (m_VolumeRendering == NULL) return;

	// ���� ��� ����
	m_CurrentPresetMode = val;

	// Volume Mapper ��������
	vtkSmartPointer<vtkSmartVolumeMapper> volumeMapper =
		vtkSmartVolumeMapper::SafeDownCast(m_VolumeRendering->GetMapper());
	if (volumeMapper == NULL) return;

	// ����
	double scalarRange[2];
	//AfxMessageBox(scalarRange[0]);
	//AfxMessageBox(scalarRange[1]);

	m_ImageData->GetScalarRange(scalarRange);

	TRACE1("scalarRange[0] = %lf \n", scalarRange[0]);
	TRACE1("scalarRange[1] = %lf \n", scalarRange[1]);

	double nMin = scalarRange[0];
	double nMax = scalarRange[1];
	TRACE2("nMin=%lf , nMax=%lf \n", nMin, nMax);

	//scalar range max-min 
	double fTerm = nMax - nMin;
	double c1_pos = 0.5;
	//color transFunction addpoint ����
	const int nCountItem_CTF = 4;
	//color transFunction addpoint �� x��ǥ ����
	double fbase[nCountItem_CTF];
	for (int i = 0; i < nCountItem_CTF; i++)
	{
		fbase[i] = nMin + fTerm * i * 0.25; // 25% �� ����.
	}
	double col[nCountItem_CTF][3] =
	{
		/*{ 0.0, 0.0, 0.0 },
		{ 0.7, 0.4, 0.1 },
		{ 0.6, 0.5, 0.3 },
		{ 1.0, 1.0, 1.0 }*/
		{ 0.0, 0.0, 0.0 },
		{ 0.9, 0.9, 0.9 },
		{ 0.9, 0.9, 0.9 },
		{ 1.0, 1.0, 1.0 }
	};

	// �ʱ�ȭ
	m_ColorFunc->RemoveAllPoints();
	m_OpacityFunc->RemoveAllPoints();

	// ���� �Լ� �� �÷� �Լ� ����
	switch (m_CurrentPresetMode) {
	case MIP:
		TRACE("MIP MODE\n");
		// �ִ� ��Ⱚ ���� �������� ���� �Լ� ����


		m_OpacityFunc->AddPoint(nMin, 0.0); // start	
		m_OpacityFunc->AddPoint(380.434, 0);
		m_OpacityFunc->AddPoint(850.220, 0.1);
		m_OpacityFunc->AddPoint(1536.603, 0.356);
		m_OpacityFunc->AddPoint(1536.603, 0);
		m_OpacityFunc->AddPoint(2852.169, 0.581);
		m_OpacityFunc->AddPoint(3938.941, 0);
		m_OpacityFunc->AddPoint(7199.257, 0);
		m_OpacityFunc->AddPoint(7199.257, 1);
		m_OpacityFunc->AddPoint(nMax, 0.4); // end*/

		
		for (int i = 0; i < nCountItem_CTF; i++)
		{
			fbase[i] = nMin + fTerm * i * 0.25; //  25% �� ����.
			//printf("fabase[%d] = %lf\n", i, fbase[i]);
		}

		for (int i = 0; i < nCountItem_CTF; i++)
			m_ColorFunc->AddRGBPoint(fbase[i], col[i][0], col[i][1], col[i][2]);
		
		/*m_ColorFunc->AddRGBPoint(380.434, 0.9, 0.9, 0.9);
		m_ColorFunc->AddRGBPoint(850.220, 0.9, 0.9, 0.9);
		m_ColorFunc->AddRGBPoint(1536.603, 0.9, 0.9, 0.9);
		m_ColorFunc->AddRGBPoint(2852.169, 0.9, 0.9, 0.9);
		m_ColorFunc->AddRGBPoint(3938.941, 0.9, 0.9, 0.9);
		m_ColorFunc->AddRGBPoint(7199.257, 0.9, 0.9, 0.9);*/


		/*m_ColorFunc->AddRGBPoint( nMin, 1.0, 1.0, 1.0 );
		m_ColorFunc->AddRGBPoint(nMin, 0.9, 0.9, 0.9);
		m_ColorFunc->AddRGBPoint(335.434, 0.9, 0.9, 0.9);
		m_ColorFunc->AddRGBPoint(850.220, 0.9, 0.9, 0.9);
		m_ColorFunc->AddRGBPoint(1536.603, 0.9, 0.9, 0.9);
		m_ColorFunc->AddRGBPoint(2852.169, 0.9, 0.9, 0.9);
		m_ColorFunc->AddRGBPoint(3938.941, 0.9, 0.9, 0.9);
		m_ColorFunc->AddRGBPoint(7199.257, 0.9, 0.9, 0.9);
		m_ColorFunc->AddRGBPoint( nMax, 1.0, 1.0, 1.0 );

		*/
		/*m_OpacityFunc->AddPoint(nMin, 0.0);
		m_OpacityFunc->AddPoint(nMin + fTerm * c1_pos, 0.0);
		 m_OpacityFunc->AddPoint(nMax, 1.0);*/

		// �ִ� ��� ���� ���� ��� ����
		 //volumeMapper->SetBlendModeToMaximumIntensity();
		volumeMapper->SetBlendModeToComposite();
		volumeMapper->SetRequestedRenderModeToDefault();
		break;
	case SKIN:
		TRACE("SKIN MODE \n");
		// �Ǻΰ� �� ���̴� ��� ���� ���� �� �� ���� ����
		m_ColorFunc->AddRGBPoint(nMin, 0, 0, 0);
		m_ColorFunc->AddRGBPoint(-1000, .62, .36, .18);
		m_ColorFunc->AddRGBPoint(-500, .88, .60, .29);
		m_ColorFunc->AddRGBPoint(nMax, .83, .66, 1);

		m_OpacityFunc->AddPoint(nMin, 0, 0.5, 0.0);
		m_OpacityFunc->AddPoint(-1000, 0, 0.5, 0.0);
		m_OpacityFunc->AddPoint(-500, 1.0, 0.33, 0.45);
		m_OpacityFunc->AddPoint(nMax, 1.0, 0.5, 0.0);

		TRACE2("nMin=%lf , nMax=%lf \n", nMin, nMax);
		//AfxMessageBox(nMin);
		//AfxMessageBox(nMax);
		// ���� ���� ���� ��� ����
		volumeMapper->SetBlendModeToComposite();
		break;
	case BONE:
		// ���� ������ �� ���̴� ��� ���� ���� �� �� ���� ����
		m_ColorFunc->AddRGBPoint(nMin, 0, 0, 0);
		m_ColorFunc->AddRGBPoint(142.68, 0, 0, 0);
		m_ColorFunc->AddRGBPoint(145.02, 0.62, 0.0, 0.02);
		m_ColorFunc->AddRGBPoint(192.17, 0.91, 0.45, 0.0);
		m_ColorFunc->AddRGBPoint(217.24, 0.97, 0.81, 0.61);
		m_ColorFunc->AddRGBPoint(384.35, 0.91, 0.91, 1.0);
		m_ColorFunc->AddRGBPoint(nMax, 1, 1, 1);
		TRACE("BONE MODE \n ");
		/*const int nCountItem_CTF = 4;
		double fbase[nCountItem_CTF];
		for (int i = 0; i < nCountItem_CTF; i++)
		{
			fbase[i] = nMin + fTerm * i * 0.25; // 25% �� ����.
		}
		double col[nCountItem_CTF][3] =
		{
		{ 0.0, 0.0, 0.0 }, { 0.7, 0.4, 0.1 },
		{ 0.6, 0.5, 0.3 }, { 1.0, 1.0, 1.0 }
		};
		// CTF ����
		//C_VTK(vtkColorTransferFunction, CTF1);
		for (int i = 0; i < nCountItem_CTF; i++)
			m_ColorFunc->AddRGBPoint(fbase[i], col[i][0], col[i][1], col[i][2]);*/

		m_OpacityFunc->AddPoint(nMin, 0.0);
		m_OpacityFunc->AddPoint(142.68, 0.0);
		m_OpacityFunc->AddPoint(145.02, 0.12);
		m_OpacityFunc->AddPoint(192.17, 0.56);
		m_OpacityFunc->AddPoint(217.24, 0.78);
		m_OpacityFunc->AddPoint(384.35, 0.83);
		m_OpacityFunc->AddPoint(nMax, 0.83);

		/*m_OpacityFunc->AddPoint(nMin, 0.0);
		m_OpacityFunc->AddPoint(nMin + fTerm * c1_pos, 0.0);
		m_OpacityFunc->AddPoint(nMax, 1.0);*/

		TRACE2("nMin=%lf , nMax=%lf \n", nMin, nMax);
		//TRACE(_T("\n"));
		//AfxMessageBox(nMin);
		//AfxMessageBox(nMax);

		// ���� ���� ���� ��� ����
		volumeMapper->SetBlendModeToComposite();
		break;
	}
}

vtkSmartPointer<vtkImageActor> VolumeData::GetSliceActor( int sliceType )
{
	// �����̽� Ÿ�� �˻�
	if( sliceType < 0 || sliceType >= 3 ) return NULL;

	// �����̽� Ÿ�Կ� �ش��ϴ� Actor ��ȯ
	return m_SliceActor[sliceType];
}

void VolumeData::ReadyForSliceRendering()
{
	// �����̽� �̹��� ������ �Ӽ� �ʱ�ȭ
	// DICOM �̹��� �ִ�/�ּ� ��Ⱚ
	double range[2];
	m_ImageData->GetScalarRange( range );
	TRACE("Light of DICOM Image range0 : %lf \n ", range[0]);
	TRACE("Light of DICOM Image range1 : %lf \n ", range[1]);
	TRACE("Light of DICOM Image range2 : %lf \n ", range[2]);
	// Volume �ε��� ����
	int ext[6];
	m_ImageData->GetExtent( ext );
	for (int i = 0; i < 6; i++) {
		TRACE1("m_ImageData ext[%d] = %d \n", i,ext[i]);
		//TRACE(_T("\n"));
	}
	

	// DICOM �����Ϳ� ���� �ʱ� Window / Level ���� ����
	m_SliceProperty = vtkSmartPointer<vtkImageProperty>::New();
	m_SliceProperty->SetColorLevel( (range[1] + range[0]) / 2 );
	m_SliceProperty->SetColorWindow( range[1] - range[0] );

	// �� �����̽� Ÿ�Կ� ���� ����
	for( int sliceType = 0; sliceType < 3; sliceType++ ) {
		// �����̽� �ε����� �߰���ġ ���
		switch( sliceType ) {
		case AXIAL:
			m_SliceIndex[sliceType] = (ext[4] + ext[5]) / 2;
			TRACE1("Axial Idx = %d", m_SliceIndex[AXIAL]);
			TRACE(_T("\n"));
			break;
		case CORONAL:
			m_SliceIndex[sliceType] = (ext[2] + ext[3]) / 2;
			//m_SliceIndex[sliceType] = (ext[2] + ext[1]) / 2;
			TRACE1("Coronal Idx = %d ", m_SliceIndex[CORONAL]);
			TRACE(_T("\n"));
			break;
		case SAGITTAL:
			m_SliceIndex[sliceType] = (ext[0] + ext[1]) / 2;
			TRACE1("Sagittal Idx = %d ", m_SliceIndex[SAGITTAL]);
			TRACE(_T("\n"));
			break;
		}

		// Image Reslice ����
		m_VolumeSlice[sliceType] = vtkSmartPointer<vtkImageReslice>::New();
		m_VolumeSlice[sliceType]->SetInputData( m_ImageData );
		m_VolumeSlice[sliceType]->SetOutputDimensionality( 2 );		// 2D�� �����̽�
		m_VolumeSlice[sliceType]->SetResliceAxes( 
			GetResliceMatrix( sliceType, m_SliceIndex[sliceType] ) );	// �����̽� ��� ����
		m_VolumeSlice[sliceType]->Update();

		// �̹��� Actor ����
		m_SliceActor[sliceType] = vtkSmartPointer<vtkImageActor>::New();
		m_SliceActor[sliceType]->GetMapper()
			->SetInputData( m_VolumeSlice[sliceType]->GetOutput() );

		// �� �����̽��� ����� �̹��� �Ӽ� ����
		m_SliceActor[sliceType]->SetProperty( m_SliceProperty );
	}
}

vtkSmartPointer<vtkMatrix4x4> VolumeData::GetResliceMatrix( int sliceType, int sliceIdx )
{
	// �����̽� Ÿ�� �˻�
	if( sliceType < 0 || sliceType >= 3 ) return NULL;

	// Slice Ÿ�Կ� ���� Orientation ���
	double sliceMat[3][16] = {
		{ // Axial �� ���
			1, 0, 0, 0,
			0, 1, 0, 0,
			0, 0, 1, 0,
			0, 0, 0, 1
		},
		{ // Coronal �� ���
			1, 0, 0, 0,
			0, 0, 1, 0,
			0, -1, 0, 0,
			0, 0, 0, 1
		},
		{ // Sagittal �� ���
			0, 0, -1, 0,
			1, 0, 0, 0,
			0, -1, 0, 0,
			0, 0, 0, 1
		}
	};

	// Slice ��� ����
	vtkSmartPointer<vtkMatrix4x4> mat = vtkSmartPointer<vtkMatrix4x4>::New();
	mat->DeepCopy( sliceMat[sliceType] );

	// DICOM Volume ������ ��������
	double origin[3];
	double bounds[6];
	int ext[6];
	m_ImageData->GetOrigin( origin );	          	// Volume ����
	m_ImageData->GetBounds( bounds );				// Volume ��ġ ����
	m_ImageData->GetExtent( ext );					// Volume �ε��� ����

	for (int i = 0; i < 3; i++) { 
		TRACE2("origin[%d] = %lf \n",i, origin[i]);
		/*TRACE1("origin[0] = %lf \n",  origin[0]); 
		TRACE1("origin[1] = %lf \n", origin[1]);
		TRACE1("origin[2] = %lf \n", origin[2]);*/
	}
	// Slice ����� ��ġ�� �������� �ʱ�ȭ
	for( int i = 0; i < 3; i++ ) mat->SetElement( i, 3, origin[i] );
	
	// Slice �ε����� ���� ��ġ ���
	double pos;
	switch( sliceType ) {
	case AXIAL:
		// �����̽� ������ ����� �ִ�/�ּ� ������ ����
		if( sliceIdx < ext[4] ) sliceIdx = ext[4];
		if( sliceIdx > ext[5] ) sliceIdx = ext[5];
		// slice �ε����� ���� ��ġ ���
		pos = bounds[4] + (bounds[5] - bounds[4]) * (double)(sliceIdx / (double)ext[5]);
		TRACE1("Axial->pos : %lf \n", pos);
		// z�� ��ġ�� �ش��ϴ� slice �ε����� ��ġ�� ����
		mat->SetElement( 2, 3, pos );
		break;
	case CORONAL:
		// �����̽� ������ ����� �ִ�/�ּ� ������ ����
		if( sliceIdx < ext[2] ) sliceIdx = ext[2];
		if( sliceIdx > ext[3] ) sliceIdx = ext[3];
		// slice �ε����� ���� ��ġ ���
		pos = bounds[2] + (bounds[3] - bounds[2]) * (double)(sliceIdx / (double)ext[3]);
		TRACE("Coronal->pos : %lf \n", pos);
		// y�� ��ġ�� �ش��ϴ� slice �ε����� ��ġ�� ����
		mat->SetElement( 1, 3, pos );
		break;
	case SAGITTAL:
		// �����̽� ������ ����� �ִ�/�ּ� ������ ����
		if( sliceIdx < ext[0] ) sliceIdx = ext[0];
		if( sliceIdx > ext[1] ) sliceIdx = ext[1];
		// slice �ε����� ���� ��ġ ���
		pos = bounds[0] + (bounds[1] - bounds[0]) * (double)(sliceIdx / (double)ext[1]);
		TRACE1("Sagittal->pos : %lf", pos);
		// x�� ��ġ�� �ش��ϴ� slice �ε����� ��ġ�� ����
		mat->SetElement( 0, 3, pos );
		break;
	}

	return mat;
}

int VolumeData::GetSliceIndex( int sliceType )
{
	// �����̽� Ÿ�� �˻�
	if( sliceType < 0 || sliceType >= 3 ) return 0;

	// ���� �����̽� �ε��� ��ȯ
	return m_SliceIndex[sliceType];
}

void VolumeData::SetSliceIndex( int sliceType, int sliceIndex )
{
	// �����̽� Ÿ�� �˻�
	if( sliceType < 0 || sliceType >= 3 ) return;

	// ���� �����̽� �ε��� ����
	m_SliceIndex[sliceType] = sliceIndex;

	// �����̽� ��� ������Ʈ
	m_VolumeSlice[sliceType]->SetResliceAxes( 
		GetResliceMatrix( sliceType, m_SliceIndex[sliceType] ) );
	m_VolumeSlice[sliceType]->Update();
}

/*void VolumeData::ActionView()
{
	BOOL bRotation = TRUE;

	
	vtkSmartPointer<vtkImageActor> sagittal = 
		vtkSmartPointer<vtkImageActor>::New();
	vtkSmartPointer<vtkImageActor> axial = 
		vtkSmartPointer<vtkImageActor>::New();
	vtkSmartPointer<vtkImageActor> coronal = 
		vtkSmartPointer<vtkImageActor>::New();
	vtkSmartPointer<vtkDICOMImageReader> reader = vtkSmartPointer<vtkDICOMImageReader>::New();
	CMainFrame mf;
	const char* dest;
	CString strInitPath = _T("D:\\user2\\Desktop\\DICOM\\");
	CFolderPickerDialog Picker(strInitPath, OFN_FILEMUSTEXIST, NULL, 0);
	reader->SetDirectoryName(dest);
	reader->Update();

	double renderer_bounds[6];
	DVManager::Mgr()->GetRenderer(DVManager::VIEW_3D)->ComputeVisiblePropBounds(renderer_bounds);

	int axial_num_max = renderer_bounds[5] / reader->GetPixelSpacing()[2];
	int coronal_num_max = renderer_bounds[1] / reader->GetPixelSpacing()[0];
	int sag_num_max = renderer_bounds[3] / reader->GetPixelSpacing()[1];

	int sag_num_A = (int)sag_num_max / 2;
	int coronal_num_A = (int)coronal_num_max / 2;
	int axial_num_A = (int)axial_num_max / 2;

	// Now we are creating three orthogonal planes passing through the
		// volume. Each plane uses a different texture map and therefore has
		// different coloration.


		// Start by creating a black/white lookup table.
	vtkSmartPointer<vtkLookupTable> bwLut = vtkSmartPointer<vtkLookupTable>::New();
	bwLut->SetTableRange(0, 2000);
	bwLut->SetSaturationRange(0, 0);
	bwLut->SetHueRange(0, 0);
	bwLut->SetValueRange(0, 1);
	bwLut->Build(); //effective built

	// Now create a lookup table that consists of the full hue circle (from HSV).
	vtkSmartPointer<vtkLookupTable> hueLut = vtkSmartPointer<vtkLookupTable>::New();
	hueLut->SetTableRange(0, 2000);
	hueLut->SetHueRange(0, 1);
	hueLut->SetSaturationRange(1, 1);
	hueLut->SetValueRange(1, 1);
	hueLut->Build(); //effective built

	// Finally, create a lookup table with a single hue but having a range in the saturation of the hue.
	vtkSmartPointer<vtkLookupTable> satLut = vtkSmartPointer<vtkLookupTable>::New();
	satLut->SetTableRange(0, 2000);
	satLut->SetHueRange(.6, .6);
	satLut->SetSaturationRange(0, 1);
	satLut->SetValueRange(1, 1);
	satLut->Build(); //effective built

	// Create the first of the three planes. The filter vtkImageMapToColors
	// maps the data through the corresponding lookup table created above.  The
	// vtkImageActor is a type of vtkProp and conveniently displays an image on
	// a single quadrilateral plane. It does this using texture mapping and as
	// a result is quite fast. (Note: the input image has to be unsigned char
	// values, which the vtkImageMapToColors produces.) Note also that by
	// specifying the DisplayExtent, the pipeline requests data of this extent
	// and the vtkImageMapToColors only processes a slice of data.
	vtkSmartPointer<vtkImageMapToColors> sagittalColors = vtkSmartPointer<vtkImageMapToColors>::New();

	
	sagittalColors->SetInputConnection(m_VolumeSlice[2]->GetOutputPort());
	sagittalColors->SetLookupTable(bwLut);
	sagittalColors->Update();

	//		vtkSmartPointer<vtkImageActor> sagittal = vtkSmartPointer<vtkImageActor>::New();
	sagittal->GetMapper()->SetInputConnection(sagittalColors->GetOutputPort());
	sagittal->SetDisplayExtent(sag_num_A, sag_num_A, 0, coronal_num_max, 0, axial_num_max);
	sagittal->ForceOpaqueOn();

	// Create the second (axial) plane of the three planes. We use the
	// same approach as before except that the extent differs.
	vtkSmartPointer<vtkImageMapToColors> axialColors = vtkSmartPointer<vtkImageMapToColors>::New();

	if (bRotation)
		axialColors->SetInputConnection(m_VolumeSlice[0]->GetOutputPort());
	else
		axialColors->SetInputConnection(reader->GetOutputPort());

	axialColors->SetLookupTable(hueLut);
	axialColors->Update();

	//		vtkSmartPointer<vtkImageActor> axial = vtkSmartPointer<vtkImageActor>::New();
	axial->GetMapper()->SetInputConnection(axialColors->GetOutputPort());
	axial->SetDisplayExtent(0, sag_num_max, 0, coronal_num_max, axial_num_A, axial_num_A);
	axial->ForceOpaqueOn();

	// Create the third (coronal) plane of the three planes. We use
	// the same approach as before except that the extent differs.
	vtkSmartPointer<vtkImageMapToColors> coronalColors = vtkSmartPointer<vtkImageMapToColors>::New();

	if (bRotation)
		coronalColors->SetInputConnection(m_VolumeSlice[1]->GetOutputPort());
	else
		coronalColors->SetInputConnection(reader->GetOutputPort());

	coronalColors->SetLookupTable(satLut);
	coronalColors->Update();

	//		vtkSmartPointer<vtkImageActor> coronal = vtkSmartPointer<vtkImageActor>::New();
	coronal->GetMapper()->SetInputConnection(coronalColors->GetOutputPort());
	coronal->SetDisplayExtent(0, sag_num_max, coronal_num_A, coronal_num_A, 0, axial_num_max);
	coronal->ForceOpaqueOn();
}*/
