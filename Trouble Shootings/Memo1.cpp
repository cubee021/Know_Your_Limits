/*기존 코드
if (DegreeSum < 180)
{
		FRotator NewRotation = FRotator(2.f, 0.f, 0.f); // 프레임마다 2.f씩 회전
		...
*/

/*수정한 코드*/
if (DegreeSum < 360)
	FRotator NewRotation = FRotator(DeltaTime * 10, 0.f, 0.f); // DeltaTime*10씩 회전
FQuat QuatRotation = FQuat(NewRotation);
...