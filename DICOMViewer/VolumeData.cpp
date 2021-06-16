#include "stdafx.h"
#include "VolumeData.h"

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
	smartMapper->SetInputData( m_ImageData );

	// ���� �Լ�, �÷� �Լ� �غ�
	double scalarRange[2];
	m_ImageData->GetScalarRange( scalarRange );
	TRACE2("scalar[0] = %lf scalar[1] = %lf \n", scalarRange[0], scalarRange[1]);
	m_OpacityFunc = vtkSmartPointer<vtkPiecewiseFunction>::New();
	//m_OpacityFunc->AdjustRange( scalarRange );
	m_ColorFunc = vtkSmartPointer<vtkColorTransferFunction>::New();
	
	// Volume �Ӽ� �غ�
	vtkSmartPointer<vtkVolumeProperty> volumeProperty = 
		vtkSmartPointer<vtkVolumeProperty>::New();
	
	volumeProperty->SetColor(0 ,m_ColorFunc );
	volumeProperty->ShadeOn();
	volumeProperty->SetInterpolationTypeToLinear();

	//0616 ����
	volumeProperty->SetDiffuse(0.7);
	volumeProperty->SetSpecular(0.3);
	volumeProperty->SetSpecularPower(30.0);
	volumeProperty->SetScalarOpacity(0, m_OpacityFunc);
	
	
	// Volume ȸ�� ��ȯ 
	double origin[3];
	m_ImageData->GetOrigin( origin );
	vtkSmartPointer<vtkTransform> userTransform = 
		vtkSmartPointer<vtkTransform>::New();
	userTransform->Translate( origin );
	userTransform->Concatenate( GetOrientation() );
	userTransform->Translate( -origin[0], -origin[1], -origin[2] );
	userTransform->Update();

	// Volume ������ ��ü ����
	m_VolumeRendering = vtkSmartPointer<vtkVolume>::New();
	m_VolumeRendering->SetMapper( smartMapper );
	m_VolumeRendering->SetProperty( volumeProperty );
	m_VolumeRendering->SetUserTransform( userTransform );

	//������ ��� �غ�
	SetCurrentPresetMode( MIP );
}

void VolumeData::SetCurrentPresetMode( int val )
{
	// Volume Rendering �غ� ����
	if( m_VolumeRendering == NULL ) return;

	// ���� ��� ����
	m_CurrentPresetMode = val;

	// Volume Mapper ��������
	vtkSmartPointer<vtkSmartVolumeMapper> volumeMapper = 
		vtkSmartVolumeMapper::SafeDownCast( m_VolumeRendering->GetMapper() );
	if( volumeMapper == NULL ) return;

	// ����
	double scalarRange[2];
	//AfxMessageBox(scalarRange[0]);
	//AfxMessageBox(scalarRange[1]);
	
	m_ImageData->GetScalarRange( scalarRange );
	TRACE1("scalarRange[0] = %lf \n", scalarRange[0]);
	TRACE1("scalarRange[1] = %lf \n", scalarRange[1]);
	double nMin= scalarRange[0];
	double nMax= scalarRange[1];
	TRACE2("nMin=%lf , nMax=%lf \n", nMin, nMax);

	double fTerm = nMax - nMin;
	double c1_pos = 0.5;

	// �ʱ�ȭ
	m_ColorFunc->RemoveAllPoints();
	m_OpacityFunc->RemoveAllPoints();
	
	// ���� �Լ� �� �÷� �Լ� ����
	switch( m_CurrentPresetMode ) {
	case MIP:
		TRACE("MIP MODE\n");
		// �ִ� ��Ⱚ ���� �������� ���� �Լ� ����


		m_OpacityFunc->AddPoint(nMin, 0.0);
		//m_OpacityFunc->AddPoint(nMin + fTerm * c1_pos, 0.0);
		m_OpacityFunc->AddPoint(nMax, 1.0);

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
	
		for (int i = 0; i < nCountItem_CTF; i++)
			m_ColorFunc->AddRGBPoint(fbase[i], col[i][0], col[i][1], col[i][2]);
			*/


		m_ColorFunc->AddRGBPoint( nMin, 1.0, 1.0, 1.0 );
 		m_ColorFunc->AddRGBPoint( nMax, 1.0, 1.0, 1.0 );
			   
		/*m_OpacityFunc->AddPoint(nMin, 0.0);
		m_OpacityFunc->AddPoint(nMin + fTerm * c1_pos, 0.0);
		m_OpacityFunc->AddPoint(nMax, 1.0);*/

		// �ִ� ��� ���� ���� ��� ����
		volumeMapper->SetBlendModeToMaximumIntensity();
		break;
	case SKIN:
		TRACE("SKIN MODE \n");
		// �Ǻΰ� �� ���̴� ��� ���� ���� �� �� ���� ����
		m_ColorFunc->AddRGBPoint( nMin, 0, 0, 0 );
		m_ColorFunc->AddRGBPoint( -1000, .62, .36, .18 );
		m_ColorFunc->AddRGBPoint( -500, .88, .60, .29 );
		m_ColorFunc->AddRGBPoint( nMax, .83, .66, 1 );

		m_OpacityFunc->AddPoint( nMin, 0, 0.5, 0.0 );
		m_OpacityFunc->AddPoint( -1000, 0, 0.5, 0.0 );
		m_OpacityFunc->AddPoint( -500, 1.0, 0.33, 0.45 );
		m_OpacityFunc->AddPoint( nMax, 1.0, 0.5, 0.0 );
		
		TRACE2("nMin=%lf , nMax=%lf \n", nMin, nMax);
		//AfxMessageBox(nMin);
		//AfxMessageBox(nMax);
		// ���� ���� ���� ��� ����
		volumeMapper->SetBlendModeToComposite();
		break;
	case BONE:
		// ���� ������ �� ���̴� ��� ���� ���� �� �� ���� ����
		m_ColorFunc->AddRGBPoint( nMin, 0, 0, 0 );
		m_ColorFunc->AddRGBPoint( 142.68, 0, 0, 0 );
		m_ColorFunc->AddRGBPoint( 145.02, 0.62, 0.0, 0.02 );
		m_ColorFunc->AddRGBPoint( 192.17, 0.91, 0.45, 0.0 );
		m_ColorFunc->AddRGBPoint( 217.24, 0.97, 0.81, 0.61 );
		m_ColorFunc->AddRGBPoint( 384.35, 0.91, 0.91, 1.0 );
		m_ColorFunc->AddRGBPoint( nMax, 1, 1, 1 );
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

		m_OpacityFunc->AddPoint( nMin, 0.0 );
		m_OpacityFunc->AddPoint( 142.68, 0.0 );
		m_OpacityFunc->AddPoint( 145.02, 0.12 );
		m_OpacityFunc->AddPoint( 192.17, 0.56 );
		m_OpacityFunc->AddPoint( 217.24, 0.78 );
		m_OpacityFunc->AddPoint( 384.35, 0.83 );
		m_OpacityFunc->AddPoint( nMax, 0.83 );

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
