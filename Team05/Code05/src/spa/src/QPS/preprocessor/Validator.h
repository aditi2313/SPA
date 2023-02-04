namespace qps {
class Validator {

    public:
      Query validator(Query query);
      bool DesignEntitySynonyms(std::vector<std::unique_ptr<Clause>> clauses,
                                std::vector<std::string> synonyms);
      bool isWildcard(std::vector<std::unique_ptr<Clause>> clauses);
      bool SynonymCheck(std::vector<std::unique_ptr<Clause>> clauses,
                        std::vector<std::string> synonyms);

     private:
      std::vector<std::unique_ptr<Clause>> clauses_;
      std::vector<std::string> synonyms_;
};
}  // namespace qps
