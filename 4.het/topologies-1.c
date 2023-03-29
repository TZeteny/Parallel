#include <stdio.h>
#include <locale.h>

struct mesh {
    int nodes, edges;
};
typedef struct mesh Mesh;

Mesh flat();
Mesh cube();

int main() {
    setlocale(LC_NUMERIC, ".OCP");
    int i;
    Mesh mesh;
    float ratio;
    FILE *fptr;
    fptr = fopen("topologies-1.txt", "w");

    //To n = 50, how many nodes and edges an n*n mesh contains.
    printf("n\t|nodes\t|edges\t|nodes to edges ratio\n----------------------------\n");
    fprintf(fptr, "n\tnodes\tedges\tnodes to edges ratio\n");
    for (i = 2; i <= 50; i++) {
        mesh = flat(i);
        ratio = (float)mesh.nodes / (float)mesh.edges;
        printf("%d\t|%d\t|%d\t|%.3f\n", i, mesh.nodes, mesh.edges, ratio);
        fprintf(fptr, "%d\t%d\t%d\t%.3f\n", i, mesh.nodes, mesh.edges, ratio);
    }

    //To n = 24, but with 3D meshes.
    printf("\n\nn\t|nodes\t|edges\t|nodes to edges ratio\n----------------------------\n");
    fprintf(fptr, "n\tnodes\tedges\tnodes to edges ratio\n");
    for (i = 2; i <= 24; i++) {
        mesh = cube(i);
        ratio = (float)mesh.nodes / (float)mesh.edges;
        printf("%d\t|%d\t|%d\t|%.3f\n", i, mesh.nodes, mesh.edges, ratio);
        fprintf(fptr, "%d\t%d\t%d\t%.3f\n", i, mesh.nodes, mesh.edges, ratio);
    }

    return 0;
}

Mesh flat(int n) {
    Mesh mesh;

    //A 2D mesh has n * n nodes.
    mesh.nodes = n * n;
    //A 2D mesh has 2 * n*(n-1) edges, which can be expressed as 2 * (n^2 - n).
    mesh.edges = 2 * (mesh.nodes - n);

    return mesh;
}

Mesh cube(int n) {
    Mesh mesh;

    //A 3D mesh has n * n * n nodes.
    mesh.nodes = n * n * n;
    /*
    A 3D mesh has 2 * [2 * n * (n-1)] + 4*(n-1) + 4*(n-2)(n-1) edges.
    Since it is cube shaped, "2 * [2 * n * (n-1)]" is for the top and bottom faces.
    4*(n-1) is for the cube's vertical edges.
    And 4*(n-2)(n-1) are for the remaining mesh edges.
    Simplified, it is 4(2*n^2 - 3*n + 1).
    */
    mesh.edges = 4 * (2*n*n - 3*n + 1);

    return mesh;
}













