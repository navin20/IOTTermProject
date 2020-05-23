
    // !!! This file is generated using emlearn !!!

    #include <eml_trees.h>
    

EmlTreesNode sonar_nodes[12] = {
  { 0, 0.31050001084804535, 1, 2 },
  { -1, 1, -1, -1 },
  { -1, 0, -1, -1 },
  { 0, 0.3110000044107437, 1, 2 },
  { 0, 0.31450000405311584, 1, 2 },
  { 0, 0.3110000044107437, 1, 2 },
  { 0, 0.3110000044107437, 1, 2 },
  { 0, 0.31050001084804535, 1, 2 },
  { 0, 0.31450000405311584, 1, 2 },
  { 0, 0.31050001084804535, 1, 2 },
  { 0, 0.3110000044107437, 1, 2 },
  { 0, 0.31050001084804535, 1, 2 } 
};

int32_t sonar_tree_roots[10] = { 0, 3, 4, 5, 6, 7, 8, 9, 10, 11 };

EmlTrees sonar = {
        12,
        sonar_nodes,	  
        10,
        sonar_tree_roots,
    };

static inline int32_t sonar_predict_tree_0(const float *features, int32_t features_length) {
          if (features[0] < 0.31050001084804535) {
              return 1;
          } else {
              return 0;
          }
        }
        

static inline int32_t sonar_predict_tree_1(const float *features, int32_t features_length) {
          if (features[0] < 0.3110000044107437) {
              return 1;
          } else {
              return 0;
          }
        }
        

static inline int32_t sonar_predict_tree_2(const float *features, int32_t features_length) {
          if (features[0] < 0.31450000405311584) {
              return 1;
          } else {
              return 0;
          }
        }
        

static inline int32_t sonar_predict_tree_3(const float *features, int32_t features_length) {
          if (features[0] < 0.3110000044107437) {
              return 1;
          } else {
              return 0;
          }
        }
        

static inline int32_t sonar_predict_tree_4(const float *features, int32_t features_length) {
          if (features[0] < 0.3110000044107437) {
              return 1;
          } else {
              return 0;
          }
        }
        

static inline int32_t sonar_predict_tree_5(const float *features, int32_t features_length) {
          if (features[0] < 0.31050001084804535) {
              return 1;
          } else {
              return 0;
          }
        }
        

static inline int32_t sonar_predict_tree_6(const float *features, int32_t features_length) {
          if (features[0] < 0.31450000405311584) {
              return 1;
          } else {
              return 0;
          }
        }
        

static inline int32_t sonar_predict_tree_7(const float *features, int32_t features_length) {
          if (features[0] < 0.31050001084804535) {
              return 1;
          } else {
              return 0;
          }
        }
        

static inline int32_t sonar_predict_tree_8(const float *features, int32_t features_length) {
          if (features[0] < 0.3110000044107437) {
              return 1;
          } else {
              return 0;
          }
        }
        

static inline int32_t sonar_predict_tree_9(const float *features, int32_t features_length) {
          if (features[0] < 0.31050001084804535) {
              return 1;
          } else {
              return 0;
          }
        }
        

int32_t sonar_predict(const float *features, int32_t features_length) {

        int32_t votes[2] = {0,};
        int32_t _class = -1;

        _class = sonar_predict_tree_0(features, features_length); votes[_class] += 1;
    _class = sonar_predict_tree_1(features, features_length); votes[_class] += 1;
    _class = sonar_predict_tree_2(features, features_length); votes[_class] += 1;
    _class = sonar_predict_tree_3(features, features_length); votes[_class] += 1;
    _class = sonar_predict_tree_4(features, features_length); votes[_class] += 1;
    _class = sonar_predict_tree_5(features, features_length); votes[_class] += 1;
    _class = sonar_predict_tree_6(features, features_length); votes[_class] += 1;
    _class = sonar_predict_tree_7(features, features_length); votes[_class] += 1;
    _class = sonar_predict_tree_8(features, features_length); votes[_class] += 1;
    _class = sonar_predict_tree_9(features, features_length); votes[_class] += 1;
    
        int32_t most_voted_class = -1;
        int32_t most_voted_votes = 0;
        for (int32_t i=0; i<2; i++) {

            if (votes[i] > most_voted_votes) {
                most_voted_class = i;
                most_voted_votes = votes[i];
            }
        }
        return most_voted_class;
    }
    