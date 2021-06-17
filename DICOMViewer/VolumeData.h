#pragma once

#include <vtkObject.h>
#include <vtkSmartPointer.h>
#include <vtkImageData.h>
#include <vtkTransform.h>
#include <vtkMatrix4x4.h>
#include <vtkVolume.h>
#include <vtkVolumeProperty.h>
#include <vtkSmartVolumeMapper.h>
#include <vtkPiecewiseFunction.h>
#include <vtkColorTransferFunction.h>
#include <vtkImageReslice.h>
#include <vtkImageActor.h>
#include <vtkImageMapper3D.h>
#include <vtkImageProperty.h>

class VolumeData :
	public vtkObject
{
public:
	/// vtkSmartPointer�� ���� ���� �� ����
	vtkTypeMacro( VolumeData, vtkObject );
	static VolumeData *New() { return new VolumeData; };

protected:
	/// New() �Լ� �̿��� ���� ����
	VolumeData();
	virtual ~VolumeData();
	
public:
	// Volume Slice Ÿ��
	enum SliceType { AXIAL, CORONAL, SAGITTAL };

	// �̸� ���ǵ� Volume ������ ���� �Լ� �� �÷� �Լ�
	enum RenderingPreset { MIP, SKIN, BONE, BONE_ARTERIES };

protected:
	/// VTK 3���� �̹��� (Volume) ������
	vtkSmartPointer<vtkImageData> m_ImageData;

	/// Volume �������� ȸ���̵� ����
	vtkSmartPointer<vtkMatrix4x4> m_Orientation;

	/// Volume ������ ��ü
	vtkSmartPointer<vtkVolume> m_VolumeRendering;
	
	/// Volume ������ ���� �Լ�
	vtkSmartPointer<vtkPiecewiseFunction> m_OpacityFunc;

	/// Volume ������ �÷� �Լ�
	vtkSmartPointer<vtkColorTransferFunction> m_ColorFunc;

	/// ���� Volume ������ ���
	int m_CurrentPresetMode;

	/// Slice ������ ��ü (Axial, Coronal, Sagittal �����̽�)
	vtkSmartPointer<vtkImageActor> m_SliceActor[3];

	/// Slice �������� ���� Volume �ܸ� 
	vtkSmartPointer<vtkImageReslice> m_VolumeSlice[3];

	/// Slice ������ �Ӽ�
	vtkSmartPointer<vtkImageProperty> m_SliceProperty;

	/// Slice �ε���
	int m_SliceIndex[3];

public:	
	/// VTK Volume ������ ��������/�����ϱ�
	vtkSmartPointer<vtkImageData> GetImageData() const { return m_ImageData; }
	void SetImageData( vtkSmartPointer<vtkImageData> val ) { m_ImageData = val; }
	
	/// Volume �������� ȸ���̵� ���� ��������/�����ϱ�
	vtkSmartPointer<vtkMatrix4x4> GetOrientation() const { return m_Orientation; }
	void SetOrientation( vtkSmartPointer<vtkMatrix4x4> val ) { m_Orientation = val; }

	/// Volume ������ ��ü
	vtkSmartPointer<vtkVolume> GetVolumeRendering() const { return m_VolumeRendering; }

	/// 3D Volume ������ �غ�
	void ReadyForVolumeRendering()
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
	
	/// ���� Volume ������ ���
	int GetCurrentPresetMode() const { return m_CurrentPresetMode; }

	/// Volume ������ ��� ����
	void SetCurrentPresetMode( int val );

	/// Slice ������ ��ü
	vtkSmartPointer<vtkImageActor> GetSliceActor( int sliceType );

	/// Slice ������ �غ�
	void ReadyForSliceRendering();

	/// Slice Ÿ�԰� �ε����� ���� Reslice ��� ���
	vtkSmartPointer<vtkMatrix4x4> GetResliceMatrix( int sliceType, int sliceIdx );
	
	/// ���� Slice �ε���
	int GetSliceIndex( int sliceType );

	/// Slice �ε��� ����
	void SetSliceIndex( int sliceType, int sliceIndex );
};
