/*���� �ڵ�
if (DegreeSum < 180)
{
		FRotator NewRotation = FRotator(2.f, 0.f, 0.f); // �����Ӹ��� 2.f�� ȸ��
		...
*/

/*������ �ڵ�*/
if (DegreeSum < 360)
	FRotator NewRotation = FRotator(DeltaTime * 10, 0.f, 0.f); // DeltaTime*10�� ȸ��
FQuat QuatRotation = FQuat(NewRotation);
...