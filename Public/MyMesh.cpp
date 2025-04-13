#include "MyMesh.h"

AMyMeshActor::AMyMeshActor()
{
	
	ProcMeshComponent = CreateDefaultSubobject<UProceduralMeshComponent>(TEXT("ProcMeshComponent"));
	RootComponent = ProcMeshComponent;
}

void AMyMeshActor::BeginPlay()
{
	Super::BeginPlay();
	
}

void AMyMeshActor::CreateMesh(const TArray<FVector>& Vertices, const TArray<int32>& Triangles)
{
	TArray<FVector> Normals;
	TArray<FVector2D> UV0;
	TArray<FColor> VertexColors;
	TArray<FProcMeshTangent> Tangents;

	Normals.Init(FVector(0.f, 0.f, 1.f), Vertices.Num());
	UV0.Init(FVector2D(0.f, 0.f), Vertices.Num());
	VertexColors.Init(FColor::Red, Vertices.Num());
	Tangents.Init(FProcMeshTangent(1.f, 0.f, 0.f), Vertices.Num());

	ProcMeshComponent->CreateMeshSection(0, Vertices, Triangles, Normals, UV0, VertexColors, Tangents, true);
}

